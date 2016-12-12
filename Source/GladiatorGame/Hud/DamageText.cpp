#include "GladiatorGame.h"
#include "DamageText.h"

void UDamageText::InitWidget_Implementation(int value)
{
    damage = value;
}

void UDamageText::ActionWidget_Implementation(int value)
{
    return;
}

FString UDamageText::GetDamage() const
{
    return FString::SanitizeFloat(damage);
}

