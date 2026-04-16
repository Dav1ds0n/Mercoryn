// Copyright by David Backes


#include "Widgets/MRC_TopDown_HUD.h"

void AMRC_TopDown_HUD::DrawHUD()
{
	Super::DrawHUD();

	if (bDrawSelectionRect)
	{
		DrawRect(SelectionColor, SelectionRectStart.X, SelectionRectStart.Y, SelectionRectSize.X, SelectionRectSize.Y);
	}
	if (bSelectActors)
	{
		SelectActorsInRect();
	}
}

void AMRC_TopDown_HUD::ShowSelectionRect(const FVector2D InSelectionRectStart, const FVector2D InSelectionRectSize)
{
	SelectionRectStart = InSelectionRectStart;
	SelectionRectSize = InSelectionRectSize;
	bDrawSelectionRect = true;
}

void AMRC_TopDown_HUD::HideSelectionRect()
{
	bDrawSelectionRect = false;
	bSelectActors = true;
}

void AMRC_TopDown_HUD::SelectActorsInRect()
{
	SelectedActors.Empty();
	FVector2D FirstPoint = SelectionRectStart;
	FVector2D SecondPoint = SelectionRectStart + SelectionRectSize;
	GetActorsInSelectionRectangle<AActor>(FirstPoint, SecondPoint, SelectedActors, false);
	bSelectActors = false;
}

TArray<AActor*> AMRC_TopDown_HUD::GetSelectedActors()
{
	return SelectedActors;
}
