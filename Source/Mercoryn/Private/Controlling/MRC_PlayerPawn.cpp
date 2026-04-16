// Copyright by David Backes


#include "Controlling/MRC_PlayerPawn.h"

// Sets default values
AMRC_PlayerPawn::AMRC_PlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMRC_PlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMRC_PlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMRC_PlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

