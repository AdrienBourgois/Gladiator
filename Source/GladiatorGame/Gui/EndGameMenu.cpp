

#include "GladiatorGame.h"
#include "EndGameMenu.h"

void UEndGameMenu::ClickRestart() const
{
	UGameplayStatics::OpenLevel(GetWorld(), "MapBeta");
}


void UEndGameMenu::SetTextWin(FString text)
{
	TextWin = text;
	ChangeTextWinBP();
}

