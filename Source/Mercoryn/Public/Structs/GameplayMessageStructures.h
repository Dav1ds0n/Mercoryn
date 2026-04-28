// Copyright by David Backes

#pragma once

#include "CoreMinimal.h"
#include "GameplayMessageStructures.generated.h"



USTRUCT(BlueprintType)
struct FMRC_CommonGameplayMessage
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Common Gameplay Message")
	FString MessageText;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Common Gameplay Message")
	AActor* Sender;

};