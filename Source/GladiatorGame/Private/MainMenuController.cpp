

#include "GladiatorGame.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuController.h"

void AMainMenuController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("AMainMenuController::BeginPlay()"));

	if (IsLocalPlayerController())
	{
		if (MainMenuBP)
		{
			if (!MainMenu)
			{
				MainMenu = CreateWidget<UUserWidget>(this, MainMenuBP);
				if (!MainMenu)
					return;
				MainMenu->AddToViewport();
				MainMenu->SetVisibility(ESlateVisibility::Visible);
				bShowMouseCursor = true;
			}
		}
	}
}



