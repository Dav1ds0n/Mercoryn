// Copyright by David Backes


#include "Entities/MRC_BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/FloatingPawnMovement.h"

#include "AIController.h"

#include "Kismet/KismetMathLibrary.h"


// Sets default values
AMRC_BasePawn::AMRC_BasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	CapsuleComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	CapsuleComponent->SetCanEverAffectNavigation(false);
	RootComponent = CapsuleComponent;

	// Create the mesh
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh"));
	SkeletalMesh->SetupAttachment(RootComponent);

	// Create Floating pawn movement
	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Floating Pawn Movement"));

	// Created selected indicator
	SelectedIndicator = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SelectedIndicator"));
	SelectedIndicator->SetupAttachment(RootComponent);
	SelectedIndicator->SetHiddenInGame(true);
	SelectedIndicator->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AMRC_BasePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMRC_BasePawn::OrientPawnToMovementOrientation()
{		
	if(!bIsMoving)
	{
		return;
	}

	FVector MoveDirection = (MoveTargetLocation - GetActorLocation());
	
	if (MoveDirection.Length() < TargetPrecisionRadius)
	{
		bIsMoving = false;
		CurrentSpeed = 0.f;
		return;
	}

	// Set speed
	FloatingPawnMovement->MaxSpeed = CurrentSpeed;

	// Set direction
	MoveDirection.Normalize(1);
	//AddMovementInput(MoveDirection, 1.f);



	FRotator DesiredRotation = UKismetMathLibrary::MakeRotFromX(MoveDirection);
	DesiredRotation.Pitch = 0; 
	DesiredRotation.Roll = 0;

	FRotator NewRotation = FMath::RInterpTo(GetActorRotation(), DesiredRotation, GetWorld()->GetDeltaSeconds(), CharacterTurnSpeed);	
	SetActorRotation(DesiredRotation);

}

// Called every frame
void AMRC_BasePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	OrientPawnToMovementOrientation();
}

// Called to bind functionality to input
void AMRC_BasePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMRC_BasePawn::SelectActor_Implementation(const bool Selected)
{
	if (SelectedIndicator) {
		SelectedIndicator->SetHiddenInGame(!Selected);
	}
}

void AMRC_BasePawn::MoveToLocation_Implementation(const FVector TargetLocation, const float MoveSpeed)
{
	MoveTargetLocation = TargetLocation + FVector(0,0,GetDefaultHalfHeight());	
	bIsMoving = true;
	CurrentSpeed = MoveSpeed;

	AAIController* PawnAIController = Cast<AAIController>(GetController());
	PawnAIController->MoveToLocation(TargetLocation, TargetPrecisionRadius);

}

EMRC_PawnType AMRC_BasePawn::GetPawnType_Implementation()
{
	return PawnType;
}

