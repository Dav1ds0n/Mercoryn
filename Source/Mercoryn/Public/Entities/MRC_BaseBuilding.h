// Copyright by David Backes

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MRC_BaseBuilding.generated.h"

UCLASS()
class MERCORYN_API AMRC_BaseBuilding : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMRC_BaseBuilding();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
