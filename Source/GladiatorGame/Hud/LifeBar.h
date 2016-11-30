#pragma once

#include "Blueprint/UserWidget.h"
#include "LifeBar.generated.h"

UCLASS()
class GLADIATORGAME_API ULifeBar : public UUserWidget
{
	GENERATED_BODY()

public :
	float max_life = 0.f;
	float current_life = 0.f;

	UFUNCTION(BlueprintCallable, Category="C++ Function")
	float GetPercent() const;
};
