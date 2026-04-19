// Copyright by David Backes

#pragma once

#include "CoreMinimal.h"

#include "MRC_FactionData.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FMRC_FactionData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Faction")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Faction")
	FLinearColor Color;

	FMRC_FactionData() :
		Name(TEXT("")),
		Color(FLinearColor::Red) {
	}

	FMRC_FactionData(
		FString Name,
		FLinearColor Color)
		:
		Name(Name),
		Color(Color) {
	}

};