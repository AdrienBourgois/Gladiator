

#include "GladiatorGame.h"
#include "GladiatorGameState.h"


void AGladiatorGameState::PlayerWin()
{
	UE_LOG(LogTemp, Warning, TEXT("PLAYER WIN!!!!!!"));
	UGameplayStatics::OpenLevel(GetWorld(), "MapBeta");
}

void AGladiatorGameState::AIWin()
{
	UE_LOG(LogTemp, Warning, TEXT("AI WIN!!!!!!"));
	UGameplayStatics::OpenLevel(GetWorld(), "MapBeta");
}
