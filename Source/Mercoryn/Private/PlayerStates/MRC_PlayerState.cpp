// Copyright by David Backes


#include "PlayerStates/MRC_PlayerState.h"

#include "GameFramework/GameplayMessageSubsystem.h"
#include "AbilitySystemComponent.h"

#include "AttributeSets/MRC_ResourceAttributeSet.h"
#include "Structs/ResourceData.h"


AMRC_PlayerState::AMRC_PlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));

	ResourceAttributeSet = CreateDefaultSubobject<UMRC_ResourceAttributeSet>(TEXT("ResourceAttributeSet"));

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ResourceAttributeSet->GetWoodAttribute()).AddUObject(this, &AMRC_PlayerState::WoodCountChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ResourceAttributeSet->GetStrawAttribute()).AddUObject(this, &AMRC_PlayerState::StrawCountChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ResourceAttributeSet->GetStoneAttribute()).AddUObject(this, &AMRC_PlayerState::StoneCountChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(ResourceAttributeSet->GetGoldAttribute()).AddUObject(this, &AMRC_PlayerState::GoldCountChanged);
	}
}

void AMRC_PlayerState::BeginPlay()
{
	OnResourcesCountChanged();
}

void AMRC_PlayerState::WoodCountChanged(const FOnAttributeChangeData& Data)
{
	OnResourcesCountChanged();
}

void AMRC_PlayerState::StoneCountChanged(const FOnAttributeChangeData& Data)
{
	OnResourcesCountChanged();
}

void AMRC_PlayerState::StrawCountChanged(const FOnAttributeChangeData& Data)
{
	OnResourcesCountChanged();
}

void AMRC_PlayerState::GoldCountChanged(const FOnAttributeChangeData& Data)
{
	OnResourcesCountChanged();
}



void AMRC_PlayerState::OnResourcesCountChanged()
{
	// Message Tag for resource updates
	FGameplayTag ResourceTag = FGameplayTag::RequestGameplayTag(FName("Resources.Updated"));

	// Create message to broadcast
	FResourceMessage ResourceMessage;
	TArray<FGameplayAttribute> AllResourceAttributes = ResourceMessage.ResourceAttributes;
	AbilitySystemComponent->GetAllAttributes(AllResourceAttributes);

	// broadcast the message
	UGameplayMessageSubsystem& MessageSubsystem = UGameplayMessageSubsystem::Get(this);
	MessageSubsystem.BroadcastMessage<FResourceMessage>(ResourceTag, ResourceMessage);
}

bool AMRC_PlayerState::ConsumeBuildCost(const TMap<FGameplayAttribute, int32>& BuildCosts)
{

	for (const auto& Cost : BuildCosts)
	{
		FGameplayAttribute Attribute = Cost.Key;
		int32 RequiredAmount = Cost.Value;
		float CurrentValue = AbilitySystemComponent->GetNumericAttribute(Attribute);
		if (CurrentValue < RequiredAmount)
		{
			return false;
		}
	}

	for (const auto& Cost : BuildCosts)
	{
		FGameplayAttribute Attribute = Cost.Key;
		int32 RequiredAmount = Cost.Value;
		float CurrentValue = AbilitySystemComponent->GetNumericAttribute(Attribute);
		AbilitySystemComponent->SetNumericAttributeBase(Attribute, CurrentValue - RequiredAmount);
	}

	OnResourcesCountChanged();

	return true;
}

void AMRC_PlayerState::RevertBuildCost(const TMap<FGameplayAttribute, int32>& BuildCosts)
{
	for (const auto& Cost : BuildCosts)
	{
		FGameplayAttribute Attribute = Cost.Key;
		int32 RequiredAmount = Cost.Value;
		float CurrentValue = AbilitySystemComponent->GetNumericAttribute(Attribute);
		AbilitySystemComponent->SetNumericAttributeBase(Attribute, CurrentValue + RequiredAmount);
	}

	OnResourcesCountChanged();
}
