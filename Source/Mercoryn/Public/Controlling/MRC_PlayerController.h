// Copyright by David Backes

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "Widgets/MRC_TopDown_HUD.h"

#include "MRC_PlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

class AMRC_TopDown_HUD;

/**
 *
 */
UCLASS()
class MERCORYN_API AMRC_PlayerController : public APlayerController
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

	UPROPERTY()
	TObjectPtr<AActor> SelectedActor;

	FVector2D SelectionStartPosition;
	FVector2D SelectionSize;
	TArray<AActor*> SelectedActors;

	UPROPERTY()
	TObjectPtr<AMRC_TopDown_HUD> TopDownHUD;



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
};
