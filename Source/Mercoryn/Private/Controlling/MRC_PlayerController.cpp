// Copyright by David Backes


#include "Controlling/MRC_PlayerController.h"

// Dependencies
#include "InputMappingContext.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h" 

#include "Widgets/MRC_TopDown_HUD.h"

#include "Entities/MRC_BasePawn.h"

// Interfaces
#include "Entities/Interfaces/SelectableInterface.h"
#include "Entities/Interfaces/NavigableInterface.h"


class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

//class UHitResult;

AMRC_PlayerController::AMRC_PlayerController()
{
	bShowMouseCursor = true;
}


void AMRC_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	TopDownHUD = Cast<AMRC_TopDown_HUD>(GetHUD());

}

void AMRC_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	Subsystem->ClearAllMappings();
	Subsystem->AddMappingContext(InputMapping, 0);

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);

	// Single Select action
	Input->BindAction(SelectAction, ETriggerEvent::Completed, this, &AMRC_PlayerController::Select);

	// Select Rectangle action
	Input->BindAction(SelectAction, ETriggerEvent::Started, this, &AMRC_PlayerController::SelectStart);
	Input->BindAction(SelectAction, ETriggerEvent::Triggered, this, &AMRC_PlayerController::Selecting);
	Input->BindAction(SelectAction, ETriggerEvent::Completed, this, &AMRC_PlayerController::SelectEnd);


	// Command selected action
	Input->BindAction(CommandAction, ETriggerEvent::Completed, this, &AMRC_PlayerController::CommandSelectedActors);

	// Command selected action
	Input->BindAction(CommandActionQuick, ETriggerEvent::Completed, this, &AMRC_PlayerController::CommandQuickSelectedActor);
}


// Single Select
void AMRC_PlayerController::Select(const FInputActionValue& Value)
{
	if (TopDownHUD)
	{
		FHitResult HitResult;
		GetHitResultUnderCursor(ECollisionChannel::ECC_Camera, false, HitResult);

		// Unselect previously selected Actor
		if (SelectedActors.Num() > 0)
		{
			for (AActor* SomeActor : SelectedActors)
			{
				if (SomeActor->GetClass()->ImplementsInterface(USelectableInterface::StaticClass()))
				{
					ISelectableInterface::Execute_SelectActor(SomeActor, false);
				}
			}
		}

		SelectedActors.Empty();

		AActor* SelectedActor = HitResult.GetActor();

		if (SelectedActor)
		{

			// Select BasePawn		
			if (SelectedActor->GetClass()->ImplementsInterface(USelectableInterface::StaticClass()))
			{
				ISelectableInterface::Execute_SelectActor(SelectedActor, true);
				SelectedActors.AddUnique(SelectedActor);
			}
		}
		OnActorsSelected.Broadcast(SelectedActors);
	}
}

// Actor Rectangle selection
void AMRC_PlayerController::SelectStart(const FInputActionValue& Value)
{
	float MouseX, MouseY;
	GetMousePosition(MouseX, MouseY);
	SelectionStartPosition = FVector2D(MouseX, MouseY);
}

void AMRC_PlayerController::Selecting(const FInputActionValue& Value)
{
	float MouseX, MouseY;
	GetMousePosition(MouseX, MouseY);
	SelectionSize = FVector2D(MouseX - SelectionStartPosition.X, MouseY - SelectionStartPosition.Y);
	if (TopDownHUD)
	{
		TopDownHUD->ShowSelectionRect(SelectionStartPosition, SelectionSize);
	}
}

void AMRC_PlayerController::SelectEnd(const FInputActionValue& Value)
{
	if (TopDownHUD)
	{
		TopDownHUD->HideSelectionRect();

		FTimerHandle TimerHandleSelectMultipleActors;
		GetWorld()->GetTimerManager().SetTimer(TimerHandleSelectMultipleActors, this, &AMRC_PlayerController::SelectMultipleActors, 0.1f, false);
	}
}

void AMRC_PlayerController::SelectMultipleActors()
{
	if (TopDownHUD)
	{
		// Unselect previous selection
		for (AActor* SomeActor : SelectedActors)
		{
			if (SomeActor)
			{
				if (SomeActor->GetClass()->ImplementsInterface(USelectableInterface::StaticClass()))
				{
					ISelectableInterface::Execute_SelectActor(SomeActor, false);
				}
			}
		}

		SelectedActors.Empty();

		// Select new actors
		TArray<AActor*> AllSelectedActors = TopDownHUD->GetSelectedActors();

		if (AllSelectedActors.Num() == 1)
		{
			AActor* SomeActor = AllSelectedActors[0];
			if (SomeActor->GetClass()->ImplementsInterface(USelectableInterface::StaticClass()))
			{
				ISelectableInterface::Execute_SelectActor(SomeActor, true);
				SelectedActors.AddUnique(SomeActor);
			}
		}
		else
		{
			for (AActor* SomeActor : AllSelectedActors)
			{
				if (SomeActor)
				{
					if (SomeActor->GetClass()->ImplementsInterface(UMRC_FactionInterface::StaticClass()))
					{
						int32 ActorFaction = IMRC_FactionInterface::Execute_GetFaction(SomeActor);
						if (FactionID != ActorFaction) {
							continue;
						}
					}

					if (SomeActor->GetClass()->ImplementsInterface(USelectableInterface::StaticClass()))
					{
						ISelectableInterface::Execute_SelectActor(SomeActor, true);
						SelectedActors.AddUnique(SomeActor);
					}
				}
			}
		}
		OnActorsSelected.Broadcast(SelectedActors);
	}
}

// Commanding Actors
void AMRC_PlayerController::CommandSelectedActors(const FInputActionValue& Value)
{
	NavigateToTarget(400.f);
}

void AMRC_PlayerController::CommandQuickSelectedActor(const FInputActionValue& Value)
{
	NavigateToTarget(600.f);
}

void AMRC_PlayerController::NavigateToTarget(const float MovementSpeed)
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECollisionChannel::ECC_Camera, false, HitResult);

	if (!HitResult.bBlockingHit)
	{
		return;
	}

	if (SelectedActors.Num() > 0)
	{
		int i = SelectedActors.Num() / -2;
		for (AActor* SomeActor : SelectedActors)
		{
			if (SomeActor->GetClass()->ImplementsInterface(UMRC_FactionInterface::StaticClass()))
			{
				int32 ActorFaction = IMRC_FactionInterface::Execute_GetFaction(SomeActor);
				if (ActorFaction != FactionID) {
					return;
				}
			}

			if (SomeActor->GetClass()->ImplementsInterface(UNavigableInterface::StaticClass()))
			{
				INavigableInterface::Execute_MoveToLocation(SomeActor, HitResult.Location + FVector(0, 100 * i, 0), MovementSpeed);
			}
		}
	}
}

// Faction
void AMRC_PlayerController::SetFaction_Implementation(const int32 NewFaction)
{
	FactionID = NewFaction;
}

int32 AMRC_PlayerController::GetFaction_Implementation()
{
	return FactionID;
}