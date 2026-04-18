// Copyright by David Backes

#pragma once

#include "CoreMinimal.h"
#include "Enums/MRC_PawnType.h"

#include "MRC_PawnData.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FMRC_PawnData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	EMRC_PawnType PawnType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	TSoftObjectPtr<UTexture2D> Texture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	int32 BaseHealth;

	FMRC_PawnData() :
		PawnType(EMRC_PawnType::Villager),
		DisplayName(TEXT("")),
		Texture(nullptr),
		BaseHealth(100) {
	}


	FMRC_PawnData(
		EMRC_PawnType Type,
		FString Name,
		UTexture2D* Tex,
		int32 Health)
		:
		PawnType(Type),
		DisplayName(Name),
		Texture(Tex),
		BaseHealth(Health) {
	}




};
