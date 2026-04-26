// Copyright by David Backes

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"

#include "MRC_ResourceAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName,PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class MERCORYN_API UMRC_ResourceAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadOnly, Category = "Resources", ReplicatedUsing = OnRep_Wood)
	FGameplayAttributeData Wood;
	ATTRIBUTE_ACCESSORS(UMRC_ResourceAttributeSet, Wood);

	UPROPERTY(BlueprintReadOnly, Category = "Resources", ReplicatedUsing = OnRep_Straw)
	FGameplayAttributeData Straw;
	ATTRIBUTE_ACCESSORS(UMRC_ResourceAttributeSet, Straw);

	UPROPERTY(BlueprintReadOnly, Category = "Resources", ReplicatedUsing = OnRep_Stone)
	FGameplayAttributeData Stone;
	ATTRIBUTE_ACCESSORS(UMRC_ResourceAttributeSet, Stone);

	UPROPERTY(BlueprintReadOnly, Category = "Resources", ReplicatedUsing = OnRep_Gold)
	FGameplayAttributeData Gold;
	ATTRIBUTE_ACCESSORS(UMRC_ResourceAttributeSet, Gold);

	UFUNCTION()
	void OnRep_Wood(const FGameplayAttributeData& OldWood);
	UFUNCTION()
	void OnRep_Straw(const FGameplayAttributeData& OldStraw);
	UFUNCTION()
	void OnRep_Stone(const FGameplayAttributeData& OldStone);
	UFUNCTION()
	void OnRep_Gold(const FGameplayAttributeData& OldGold);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

};
