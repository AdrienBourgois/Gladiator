#pragma once

#include "Blueprint/UserWidget.h"
#include "WidgetInterface.h"
#include "LifeBar.generated.h"

UCLASS()
class GLADIATORGAME_API ULifeBar : public UUserWidget, public IWidgetInterface
{
    GENERATED_BODY()

public :
    UFUNCTION(BlueprintCallable, Category="C++ Function")
    float GetPercent() const;
    UFUNCTION(BlueprintCallable, Category="C++ Function")
    FString GetCurrentLifeAsText() const;

    void InitWidget_Implementation(float value) override;
    void ActionWidget_Implementation(float value) override;
    float GetSizeX_Implementation() const override;
    float GetSizeY_Implementation() const override;

private:
    float max_life = 0.f;
    float current_life = 0.f;

    UPROPERTY(EditAnywhere)
    float size_x = 50.f;
    UPROPERTY(EditAnywhere)
    float size_y = 10.f;
};
