#pragma once

#include "WidgetInterface.generated.h"

UINTERFACE(Blueprintable)
class GLADIATORGAME_API UWidgetInterface : public UInterface
{
    GENERATED_BODY()
};

class IWidgetInterface
{    
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="C++ Function")
    void InitWidget(float value);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="C++ Function")
    void ActionWidget(float value);

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="C++ Function")
    float GetSizeX() const;
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="C++ Function")
    float GetSizeY() const;
};