// Copyright by David Backes

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/CapsuleComponent.h"

#include "Interfaces/SelectableInterface.h"

#include "MRC_BaseBuilding.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class UCapsuleComponent;

UCLASS()
class MERCORYN_API AMRC_BaseBuilding : public AActor, public ISelectableInterface
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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	// Selectable Interface
	void SelectActor_Implementation(const bool Selected) override;

};
