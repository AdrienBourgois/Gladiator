

#include "GladiatorGame.h"
#include "Blueprint/UserWidget.h"
#include "GladiatorGameController.h"


void AGladiatorGameController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalPlayerController())
	{
		if (NetworkMenuBP)
		{
			if (!NetworkMenu)
			{
				NetworkMenu = CreateWidget<UNetworkMenu>(this, NetworkMenuBP);
				if (!NetworkMenu)
					return;
				NetworkMenu->AddToViewport();
				NetworkMenu->SetVisibility(ESlateVisibility::Hidden);
			}
		}
	}
}

void AGladiatorGameController::DisplayNetworkMenu()
{
	if (NetworkMenu == nullptr)
		return;
	if (NetworkMenuIsVisible)
	{
		NetworkMenuIsVisible = false;
		NetworkMenu->SetVisibility(ESlateVisibility::Hidden);
		bShowMouseCursor = false;
	}
	else
	{
		
		NetworkMenuIsVisible = true;
		NetworkMenu->SetVisibility(ESlateVisibility::Visible);
		bShowMouseCursor = true;
	}
	
}
