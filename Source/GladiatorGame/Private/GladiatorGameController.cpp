

#include "GladiatorGame.h"
#include "Blueprint/UserWidget.h"
#include "Gui/EndGameMenu.h"
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
		if (EndGameMenuBP)
		{
			if (!EndGameMenu)
			{
				EndGameMenu = CreateWidget<UEndGameMenu>(this, EndGameMenuBP);
				if (!EndGameMenu)
					return;
				EndGameMenu->AddToViewport();
				EndGameMenu->SetVisibility(ESlateVisibility::Hidden);
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
		UGameplayStatics::SetGamePaused(GetWorld(), false);
		NetworkMenuIsVisible = false;
		NetworkMenu->SetVisibility(ESlateVisibility::Hidden);
		bShowMouseCursor = false;
	}
	else
	{
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		NetworkMenuIsVisible = true;
		NetworkMenu->SetVisibility(ESlateVisibility::Visible);
		bShowMouseCursor = true;
	}
	
}


void AGladiatorGameController::DisplayEndGameMenu(FString Text)
{
	EndGameMenu->SetTextWin(Text);
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	EndGameMenu->SetVisibility(ESlateVisibility::Visible);
	bShowMouseCursor = true;
}
