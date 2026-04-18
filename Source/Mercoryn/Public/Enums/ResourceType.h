// Copyright by David Backes

#pragma once

#include "CoreMinimal.h"

#include "ResourceType.generated.h"

/**
 * Resource types
 */

UENUM(BlueprintType)
enum class EResourceType : uint8
{
	Wood UMETA(DisplayName = "Wood"),
	Straw UMETA(DisplayName = "Straw"),
	Stone UMETA(DisplayName = "Stone"),
	Meat UMETA(DisplayName = "Meat"),
	Gold UMETA(DisplayName = "Gold"),

	Population UMETA(DisplayName = "Population")
};