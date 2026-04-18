// Copyright by David Backes

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EMRC_PawnType : uint8
{
	Villager UMETA(DisplayName = "Villager"),
	Swordman UMETA(DisplayName = "Swordman"),
	Knight UMETA(DisplayName = "Knight"),
	Archer UMETA(DisplayName = "Archer")

};
