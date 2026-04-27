// Copyright by David Backes

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"

#include "Interfaces/SelectableInterface.h"
#include "Interfaces/MRC_BaseActorInterface.h"
#include "Common/Interfaces/MRC_FactionInterface.h"

#include "Enums/MRC_ActorType.h"

#include "MRC_BaseBuilding.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UCapsuleComponent;
class UInputAction;

struct FInputActionValue;

UCLASS()
class MERCORYN_API AMRC_BaseBuilding : public AActor, public ISelectableInterface, public IMRC_FactionInterface, public IMRC_BaseActorInterface
{
	GENERATED_BODY()
	
private:	
	// Sets default values for this actor's properties
	AMRC_BaseBuilding();

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	//TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Static Mesh", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Static Mesh", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UStaticMeshComponent> SelectedIndicator;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Faction", meta = (AllowPrivateAccess = "true"))
	int32 FactionID = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building", meta = (AllowPrivateAccess = "true"))
	EMRC_ActorType ActorType = EMRC_ActorType::House;


	// Building Placement
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> PlaceAction;

	UPROPERTY()
	FTimerHandle PlacementValidationTimerHandle;
	
	UPROPERTY()
	FName RequiredTag = "CanPlaceBuildings"; // Need in Landscape for creating

	UPROPERTY()
	bool bCanPlaceBuilding = false;

	// Building Options
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building", meta = (AllowPrivateAccess = "true"))
	TArray<TSubclassOf<AMRC_BaseBuilding>> BuildOptions;

	// Building Size
	UPROPERTY()
	FVector BuildingExtents = FVector(500.0f, 500.0f, .0f); 

	// Building Costs
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Building", meta = (AllowPrivateAccess = "true"))
	UDataTable* DTBuildCosts;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Selectable Interface
	void SelectActor_Implementation(const bool Selected) override;

	void SetFaction_Implementation(const int32 NewFaction) override;

	// Faction Interface
	int32 GetFaction_Implementation() override;

	// Base Actor Interface	
	EMRC_ActorType GetActorType_Implementation() override;

	TArray<TSubclassOf<AMRC_BaseBuilding>> GetBuildOptions_Implementation() override;

	// Place Building mode
	UFUNCTION(BlueprintCallable, Category = "Building")
	void EnablePlacingMode();

	// Check location for placement
	void ValidatePlacementLocation();

	// Revert costs for building
	void RevertBuildingPlacementCost();

	// Place the building
	void PlaceBuilding(const FInputActionValue& Value);

	// Cancel Placement Building
	void CancelBuildingPlacement();

	UFUNCTION(BlueprintImplementableEvent, Category = "Building")
	void ToggleBuildingValidity(bool bValid);


};
