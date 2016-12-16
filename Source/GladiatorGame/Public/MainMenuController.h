

#pragma once

#include "GameFramework/PlayerController.h"
#include "MainMenuController.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATORGAME_API AMainMenuController : public APlayerController
{
	GENERATED_BODY()
	
	void BeginPlay();
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> MainMenuBP;
	UUserWidget* MainMenu;
};
