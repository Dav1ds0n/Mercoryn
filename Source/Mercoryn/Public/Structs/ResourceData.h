// Copyright by David Backes

#pragma once

#include "CoreMinimal.h"
//#include "Enums/MRC_ResourceTypes.h"

#include "ResourceData.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FResourceData
{
	GENERATED_USTRUCT_BODY()

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	//EMRC_ResourceTypes ResourceType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	FString DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	UTexture2D* Texture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Resource")
	int32 DefaultValue;

	FResourceData() : 
		//ResourceType(EMRC_ResourceTypes::Wood), 
		DisplayName(TEXT("")), 
		Texture(nullptr), 
		DefaultValue(0) {}


	FResourceData(
		//EMRC_ResourceTypes Type, 
		FString Name, 
		UTexture2D* Tex, 
		int32 Default)
		: 
		//ResourceType(Type), 
		DisplayName(Name), 
		Texture(Tex), 
		DefaultValue(Default) {
	}




};
