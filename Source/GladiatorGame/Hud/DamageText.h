#pragma once

#include "Blueprint/UserWidget.h"
#include "WidgetInterface.h"
#include "DamageText.generated.h"

UCLASS()
class GLADIATORGAME_API UDamageText : public UUserWidget, public IWidgetInterface
{
    GENERATED_BODY()
   
public:
    void InitWidget_Implementation(int value) override;
    void ActionWidget_Implementation(int value) override;

    UFUNCTION(BlueprintCallable, Category="C++ Function")
    FString GetDamage() const;

private:
    int damage = 0;
    
};
