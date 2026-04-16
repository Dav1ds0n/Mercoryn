// Copyright by David Backes


#include "Entities/MRC_BaseBuilding.h"

// Sets default values
AMRC_BaseBuilding::AMRC_BaseBuilding()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

