// Copyright by David Backes


#include "Entities/MRC_BaseBuilding.h"

#include "Controlling/MRC_PlayerController.h"

#include "Structs/ResourceData.h"
#include "PlayerStates/MRC_PlayerState.h"

#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"


// Sets default values
AMRC_BaseBuilding::AMRC_BaseBuilding()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	//CapsuleComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	//RootComponent = CapsuleComponent;

	// Create Mesh
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	//StaticMesh->SetupAttachment(RootComponent);
	RootComponent = StaticMesh;

	// Created selected indicator
	SelectedIndicator = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Selected Indicator"));
	SelectedIndicator->SetupAttachment(RootComponent);
	SelectedIndicator->SetHiddenInGame(true);
	SelectedIndicator->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

// Called when the game starts or when spawned
void AMRC_BaseBuilding::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AMRC_BaseBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Sectable Interface
void AMRC_BaseBuilding::SelectActor_Implementation(const bool Selected)
{
	if (SelectedIndicator) {
		SelectedIndicator->SetHiddenInGame(!Selected);
	}
}

void AMRC_BaseBuilding::SetFaction_Implementation(const int32 NewFaction)
{
	FactionID = NewFaction;
}

// Faction Interface
int32 AMRC_BaseBuilding::GetFaction_Implementation()
{
	return FactionID;
}

// Base Actor Interface

EMRC_ActorType AMRC_BaseBuilding::GetActorType_Implementation()
{
	return ActorType;
}

TArray<TSubclassOf<AMRC_BaseBuilding>> AMRC_BaseBuilding::GetBuildOptions_Implementation()
{
	return BuildOptions;
}


// Building 

void AMRC_BaseBuilding::EnablePlacingMode()
{
	// Enable input on this actor
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if (PlayerController)
	{
		EnableInput(PlayerController);
		UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerController->InputComponent);
		if (EnhancedInputComponent)
		{
			EnhancedInputComponent->BindAction(PlaceAction, ETriggerEvent::Completed, this, &AMRC_BaseBuilding::PlaceBuilding);
		}
	}

	// Start validation check timer
	GetWorld()->GetTimerManager().SetTimer(PlacementValidationTimerHandle, this, &AMRC_BaseBuilding::ValidatePlacementLocation, 0.03f, true);

	this->SetActorEnableCollision(false);

}

void AMRC_BaseBuilding::ValidatePlacementLocation()
{
	ToggleBuildingValidity(bCanPlaceBuilding);

	bCanPlaceBuilding = false;

	// set location of the building under cursor
	FHitResult HitResult;
	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

	if (!HitResult.bBlockingHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit result not blocking: %s"), *HitResult.GetActor()->GetName());
		return;
	}

	// Set lcoation to cursor
	SetActorLocation(HitResult.Location);

	if (!HitResult.GetActor()->ActorHasTag(RequiredTag))
	{
		UE_LOG(LogTemp, Warning, TEXT("Required Tag missing: %s"), *HitResult.GetActor()->GetName());
		return;
	}

	// Define parametes for box sweep
	FVector BoxHalfExtent = BuildingExtents / 2;
	FVector TraceStart = HitResult.Location + FVector(0.f, 0.f, BoxHalfExtent.Z);
	FVector TraceEnd = TraceStart + FVector::UpVector;

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	CollisionParams.bTraceComplex = false;

	TArray<FHitResult> OutHits;

	// Performbox sweep to check collisions
	bool bHit = GetWorld()->SweepMultiByChannel(OutHits, TraceStart, TraceEnd, GetActorRotation().Quaternion(), ECC_Visibility, FCollisionShape::MakeBox(BoxHalfExtent), CollisionParams);

	for (const FHitResult& Hit : OutHits)
	{
		if (!(Hit.GetActor() != nullptr && Hit.GetActor()->ActorHasTag(RequiredTag)))
		{
			return;
		}
	}

	bCanPlaceBuilding = true;
}

void AMRC_BaseBuilding::RevertBuildingPlacementCost()
{
	FString sActorType = UEnum::GetValueAsString(ActorType);
	FString CleanName;
	sActorType.Split("::", nullptr, &CleanName);
	FMRC_ActorBuildCost* BuildCost = DTBuildCosts->FindRow<FMRC_ActorBuildCost>(FName(CleanName), TEXT(""));

	if (BuildCost)
	{
		AMRC_PlayerState* PlayerState = Cast<AMRC_PlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState);
		PlayerState->RevertBuildCost(BuildCost->BuildCost);
	}
}

void AMRC_BaseBuilding::PlaceBuilding(const FInputActionValue& Value)
{
	if (!bCanPlaceBuilding)
	{
		RevertBuildingPlacementCost();
		SetLifeSpan(0.1f);
		return;
	}


	// Cancel validation check timer
	GetWorld()->GetTimerManager().ClearTimer(PlacementValidationTimerHandle);

	// Set Faction ID
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController) 
	{
		AMRC_PlayerController* pc = Cast<AMRC_PlayerController>(PlayerController);
		if (pc && pc->GetClass()->ImplementsInterface(UMRC_FactionInterface::StaticClass()))
		{
			int32 ActorFaction = IMRC_FactionInterface::Execute_GetFaction(pc);
			
			if (pc && pc->GetClass()->ImplementsInterface(UMRC_FactionInterface::StaticClass()))
			{
				IMRC_FactionInterface::Execute_SetFaction(this,ActorFaction);
			}
			
		}
	}
	
	this->SetActorEnableCollision(true);
}

void AMRC_BaseBuilding::CancelBuildingPlacement()
{

}

