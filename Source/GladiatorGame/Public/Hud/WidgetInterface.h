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
    void InitWidget(int value);
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="C++ Function")
    void ActionWidget(int value);
};