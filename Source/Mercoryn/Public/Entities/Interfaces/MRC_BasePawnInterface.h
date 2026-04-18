// Copyright by David Backes

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"

#include "Enums/MRC_PawnType.h"

#include "MRC_BasePawnInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UMRC_BasePawnInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class MERCORYN_API IMRC_BasePawnInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Base Pawn Interface")
	EMRC_PawnType GetPawnType();


};
