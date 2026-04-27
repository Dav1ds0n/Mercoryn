// Copyright by David Backes

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MRC_PlayerState.generated.h"

class UMRC_ResourceAttributeSet;
class UAbilitySystemComponent;

struct FOnAttributeChangeData;

/**
 *
 */
UCLASS()
class MERCORYN_API AMRC_PlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	AMRC_PlayerState();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = "Mercoryn|Resources")
	void RevertBuildCost(const TMap<FGameplayAttribute, int32>& BuildCosts);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mercoryn|Resources")
	const class UMRC_ResourceAttributeSet* ResourceAttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Mercoryn|Resources")
	UAbilitySystemComponent* AbilitySystemComponent;

	virtual void WoodCountChanged(const FOnAttributeChangeData& Data);
	virtual void StoneCountChanged(const FOnAttributeChangeData& Data);
	virtual void StrawCountChanged(const FOnAttributeChangeData& Data);
	virtual void GoldCountChanged(const FOnAttributeChangeData& Data);

	UFUNCTION(BlueprintCallable, Category = "Mercoryn|Resources")
	void OnResourcesCountChanged();

	UFUNCTION(BlueprintCallable, Category = "Mercoryn|Resources")
	bool ConsumeBuildCost(const TMap<FGameplayAttribute,int32>& BuildCosts);

};
