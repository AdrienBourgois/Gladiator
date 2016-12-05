#pragma once

#include "Blueprint/UserWidget.h"
#include "WidgetInterface.h"
#include "LifeBar.generated.h"

UCLASS()
class GLADIATORGAME_API ULifeBar : public UUserWidget, public IWidgetInterface
{
	GENERATED_BODY()

public :
	float max_life = 0.f;
	float current_life = 0.f;

	UFUNCTION(BlueprintCallable, Category="C++ Function")
	float GetPercent() const;
	UFUNCTION(BlueprintCallable, Category="C++ Function")
	FString GetCurrentLifeAsText() const;


	void InitWidget_Implementation(int value) override;
	void ActionWidget_Implementation(int value) override;
};
