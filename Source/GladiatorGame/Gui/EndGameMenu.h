

#pragma once

#include "Blueprint/UserWidget.h"
#include "EndGameMenu.generated.h"

/**
 * 
 */
UCLASS()
class GLADIATORGAME_API UEndGameMenu : public UUserWidget
{
	GENERATED_BODY()

public :

	UFUNCTION(BlueprintCallable, Category="C++ Function")
	void ClickRestart() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString TextWin;

	void SetTextWin(FString text);

	UFUNCTION(BlueprintImplementableEvent)
	void ChangeTextWinBP();
};
