// Copyright by David Backes


#include "AttributeSets/MRC_ResourceAttributeSet.h"
#include "Net/UnrealNetwork.h"


void UMRC_ResourceAttributeSet::OnRep_Wood(const FGameplayAttributeData& OldWood)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMRC_ResourceAttributeSet, Wood, OldWood);
}

void UMRC_ResourceAttributeSet::OnRep_Straw(const FGameplayAttributeData& OldStraw)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMRC_ResourceAttributeSet, Straw, OldStraw);
}

void UMRC_ResourceAttributeSet::OnRep_Stone(const FGameplayAttributeData& OldStone)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMRC_ResourceAttributeSet, Stone, OldStone);
}

void UMRC_ResourceAttributeSet::OnRep_Gold(const FGameplayAttributeData& OldGold)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UMRC_ResourceAttributeSet, Gold, OldGold);
}

void UMRC_ResourceAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UMRC_ResourceAttributeSet, Wood, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMRC_ResourceAttributeSet, Straw, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMRC_ResourceAttributeSet, Stone, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UMRC_ResourceAttributeSet, Gold, COND_None, REPNOTIFY_Always);
}
