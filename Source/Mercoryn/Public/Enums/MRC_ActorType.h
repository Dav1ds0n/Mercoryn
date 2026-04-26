// Copyright by David Backes

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EMRC_ActorType : uint8
{
	// Pawn Types
	Villager UMETA(DisplayName = "Villager"),
	Swordman UMETA(DisplayName = "Swordman"),
	Knight UMETA(DisplayName = "Knight"),
	Archer UMETA(DisplayName = "Archer"),

	// Buildings Types
	House UMETA(DisplayName = "House"),
	Spring UMETA(DisplayName = "Spring"),

};
