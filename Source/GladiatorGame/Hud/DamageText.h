#pragma once

#include "Blueprint/UserWidget.h"
#include "WidgetInterface.h"
#include "DamageText.generated.h"

UCLASS()
class GLADIATORGAME_API UDamageText : public UUserWidget, public IWidgetInterface
{
    GENERATED_BODY()
   
public:
    void InitWidget_Implementation(float value) override;
    void ActionWidget_Implementation(float value) override;

    UFUNCTION(BlueprintCallable, Category="C++ Function")
    FString GetDamage() const;
    float GetSizeX_Implementation() const override;
    float GetSizeY_Implementation() const override;

private:
    float damage = 0;

    UPROPERTY(EditAnywhere)
    float size_x = 20.f;
    UPROPERTY(EditAnywhere)
    float size_y = 20.f;
    
};
