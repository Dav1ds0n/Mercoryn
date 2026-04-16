// Copyright by David Backes

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MRC_TopDown_HUD.generated.h"

/**
 *
 */
UCLASS()
class MERCORYN_API AMRC_TopDown_HUD : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Selection", meta = (AllowPrivateAcces = "true"))
	FLinearColor SelectionColor = FLinearColor(1.f, 0.f, 0.f, 0.5f);

private:
	bool bDrawSelectionRect = false;
	bool bSelectActors = false;
	FVector2D SelectionRectStart;
	FVector2D SelectionRectSize;

	TArray<AActor*> SelectedActors;

	void SelectActorsInRect();
	
protected:

	virtual void DrawHUD() override;
	
public:

	void ShowSelectionRect(const FVector2D InSelectionStartPosition, const FVector2D InSelectionRectSize);

	void HideSelectionRect();

	TArray<AActor*> GetSelectedActors();

};
