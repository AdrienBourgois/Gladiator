#include "GladiatorGame.h"
#include "LifeBar.h"

float ULifeBar::GetPercent() const
{
    if (max_life == 0.f || current_life == 0.f)
        return 0.f;
    return 1.f / max_life * current_life;
}

FString ULifeBar::GetCurrentLifeAsText() const
{
    //if(max_life > 0)
        //GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat(current_life));
    return FString::SanitizeFloat(current_life);
}

void ULifeBar::InitWidget_Implementation(float value)
{
    max_life = value;
    current_life = value;
}

void ULifeBar::ActionWidget_Implementation(float value)
{
    current_life = value;
}

float ULifeBar::GetSizeX_Implementation() const
{
    return size_x;
}

float ULifeBar::GetSizeY_Implementation() const
{
    return size_y;
}