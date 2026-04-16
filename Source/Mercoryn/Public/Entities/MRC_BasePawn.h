// Copyright by David Backes

#pragma once

// Dependencies
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"

// Interfaces
#include "Interfaces/SelectableInterface.h"
#include "Interfaces/NavigableInterface.h"

#include "MRC_BasePawn.generated.h"

class UCapsuleComponent;
class USkeletalMeshCompnent;
class UFloatingPawnMovement;
class UStaticMeshComponent;

UCLASS()
class MERCORYN_API AMRC_BasePawn : public APawn, public ISelectableInterface, public INavigableInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMRC_BasePawn();

private:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USkeletalMeshComponent> SkeletalMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UFloatingPawnMovement> FloatingPawnMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pawn", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> SelectedIndicator;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Navigation

	void OrientPawnToMovementOrientation();

	FVector MoveTargetLocation = FVector::ZeroVector;
	bool bIsMoving = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float TargetPrecisionRadius = 50.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float CharacterTurnSpeed = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float WalkSpeed = 200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	float RunSpeed = 500.f;


private:
	float CurrentSpeed = 0.f;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	UFUNCTION()
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// Selectable Interface
	void SelectActor_Implementation(const bool Selected) override;

	// Navigable Interface
	void MoveToLocation_Implementation(const FVector TargetLocation, const float MoveSpeed) override;
};
