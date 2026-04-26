// Copyright by David Backes

#pragma once

#include "CoreMinimal.h"
#include "Enums/MRC_ActorType.h"

#include "MRC_ActorData.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FMRC_ActorData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	EMRC_ActorType ActorType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	TSoftObjectPtr<UTexture2D> Texture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	TSoftObjectPtr<UMaterialInterface> IconMaterial;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	int32 BaseHealth;

	FMRC_ActorData() :
		ActorType(EMRC_ActorType::Villager),
		DisplayName(TEXT("")),
		Texture(nullptr),
		BaseHealth(100) {
	}


	FMRC_ActorData(
		EMRC_ActorType Type,
		FString Name,
		UTexture2D* Tex,
		int32 Health)
		:
		ActorType(Type),
		DisplayName(Name),
		Texture(Tex),
		BaseHealth(Health) {
	}




};
