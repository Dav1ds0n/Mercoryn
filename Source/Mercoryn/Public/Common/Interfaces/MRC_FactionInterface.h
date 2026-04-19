// Copyright by David Backes

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MRC_FactionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMRC_FactionInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class MERCORYN_API IMRC_FactionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Faction")
	int32 GetFaction();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Faction")
	void SetFaction(int32 NewFaction);

};
