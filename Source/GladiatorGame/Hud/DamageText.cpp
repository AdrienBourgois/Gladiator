#include "GladiatorGame.h"
#include "DamageText.h"

void UDamageText::InitWidget_Implementation(float value)
{
    damage = value;
}

void UDamageText::ActionWidget_Implementation(float value)
{
    return;
}

FString UDamageText::GetDamage() const
{
    if (damage == 2.f)
        return FString(TEXT("Dead !"));
    return FString(TEXT("Hit !"));
}

float UDamageText::GetSizeX_Implementation() const
{
    return size_x;
}

float UDamageText::GetSizeY_Implementation() const
{
    return size_y;
}