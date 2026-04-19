// Copyright by David Backes


#include "Entities/MRC_BaseBuilding.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"

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

int32 AMRC_BaseBuilding::GetFaction_Implementation()
{
	return FactionID;
}

