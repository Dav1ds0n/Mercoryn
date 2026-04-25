// Copyright by David Backes

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "Widgets/MRC_TopDown_HUD.h"

#include "Common/Interfaces/MRC_FactionInterface.h"

#include "MRC_PlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

class AMRC_TopDown_HUD;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorsSelectedDelegate, const TArray<AActor*>&, SelectedActors);

/**
 *
 */
UCLASS()
class MERCORYN_API AMRC_PlayerController : public APlayerController, public IMRC_FactionInterface
{
	GENERATED_BODY()

public:

	// Sets default values for this pawn's properties
	AMRC_PlayerController();

	UPROPERTY(EditDefaultsOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* InputMapping;

private:
	// Select action
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> SelectAction;

	UPROPERTY(BlueprintAssignable,Category = "Delegates")
	FOnActorsSelectedDelegate OnActorsSelected;		

	
	FVector2D SelectionStartPosition;
	FVector2D SelectionSize;
	UPROPERTY()
	TArray<AActor*> SelectedActors;

	UPROPERTY()
	TObjectPtr<AMRC_TopDown_HUD> TopDownHUD;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Faction", meta = (AllowPrivateAccess = "true"))
	int32 FactionID = 1;


	// Command action
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> CommandAction;

	// Command action
	UPROPERTY(EditAnyWhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> CommandActionQuick;

public:

	virtual void BeginPlay() override;

	// Called to bind functionality to input
	virtual void SetupInputComponent() override;

private:
	void NavigateToTarget(const float MovementSpeed);

	void Select(const FInputActionValue& Value);

	void SelectStart(const FInputActionValue& Value);
	void Selecting(const FInputActionValue& Value);
	void SelectEnd(const FInputActionValue& Value);
	void SelectMultipleActors();


	void CommandSelectedActors(const FInputActionValue& Value);

	void CommandQuickSelectedActor(const FInputActionValue& Value);

	void SetFaction_Implementation(const int32 NewFaction) override;

	int32 GetFaction_Implementation() override;
};
