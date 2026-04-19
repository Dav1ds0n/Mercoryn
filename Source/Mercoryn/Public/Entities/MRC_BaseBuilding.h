// Copyright by David Backes

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"

#include "Interfaces/SelectableInterface.h"
#include "Common/Interfaces/MRC_FactionInterface.h"

#include "MRC_BaseBuilding.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UCapsuleComponent;

UCLASS()
class MERCORYN_API AMRC_BaseBuilding : public AActor, public ISelectableInterface, public IMRC_FactionInterface
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


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Selectable Interface
	void SelectActor_Implementation(const bool Selected) override;


	void SetFaction_Implementation(const int32 NewFaction) override;

	int32 GetFaction_Implementation() override;

};
