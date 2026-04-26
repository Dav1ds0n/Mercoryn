// Copyright by David Backes

#include "Widgets/MRC_TopDown_HUD.h"

#include "Entities/MRC_BasePawn.h"
#include "Entities/MRC_BaseBuilding.h"


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

	// Select pawns
	TArray<AMRC_BasePawn*> SelectedPawns;
	GetActorsInSelectionRectangle<AMRC_BasePawn>(FirstPoint, SecondPoint, SelectedPawns, false);
	if (SelectedPawns.Num() > 0)
	{
		bSelectActors = false;
		// Copy selected pawns to SelectedActors
		for (AMRC_BasePawn* Pawn : SelectedPawns)
		{
			if (Pawn)
			{
				SelectedActors.AddUnique(Pawn);
			}
		}
		return;
	}

	// Select Buildings
	TArray<AMRC_BaseBuilding*> SelectedBuildings;
	GetActorsInSelectionRectangle<AMRC_BaseBuilding>(FirstPoint, SecondPoint, SelectedBuildings, false);
	if (SelectedBuildings.Num() > 0)
	{
		bSelectActors = false;
		// Copy selected Buildings to SelectedActors
		for (AMRC_BaseBuilding* Building : SelectedBuildings)
		{
			if (Building)
			{
				SelectedActors.AddUnique(Building);
			}
		}
		return;
	}
	
}

TArray<AActor*> AMRC_TopDown_HUD::GetSelectedActors()
{
	return SelectedActors;
}
