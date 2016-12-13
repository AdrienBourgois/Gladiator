

#pragma once

#include "GameFramework/PlayerController.h"
#include "Gui/NetworkMenu.h"
#include "GladiatorGameController.generated.h"

/**
 * 
 */

UCLASS()
class GLADIATORGAME_API AGladiatorGameController : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void BeginPlay();
	void DisplayNetworkMenu();
	void DisplayEndGameMenu(FString Text);

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UNetworkMenu> NetworkMenuBP;
	UNetworkMenu* NetworkMenu;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UEndGameMenu> EndGameMenuBP;
	UEndGameMenu* EndGameMenu;

private:
	bool NetworkMenuIsVisible = false;
};
