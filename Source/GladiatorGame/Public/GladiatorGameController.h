

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
	void BeginPlay();
	void DisplayNetworkMenu();

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UNetworkMenu> NetworkMenuBP;
	UNetworkMenu* NetworkMenu;

private:
	bool NetworkMenuIsVisible = false;
};
