#pragma once

#include "Components/ActorComponent.h"
#include "WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "Hud/LifeBar.h"
#include "Widget3d.generated.h"

UENUM(BlueprintType)
enum class EWidgetType : uint8
{
	LifeBar UMETA(DisplayName="LifeBar"),
};

UCLASS( ClassGroup=(Widget), meta=(BlueprintSpawnableComponent) )
class GLADIATORGAME_API UWidget3d : public UActorComponent
{
	GENERATED_BODY()

public:

	// Sets default values for this component's properties
	UWidget3d();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UFUNCTION(BlueprintCallable, Category = "C++ Function")
	void Follow(TSubclassOf<UUserWidget> _type, FVector _relative_location = FVector(0.f, 0.f, 100.f));

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	//EWidgetType type = EWidgetType::LifeBar;

	//TSubclassOf<class UUserWidget> widget_template_class;
	UUserWidget* widget_instance = nullptr;
	UWidgetComponent* widget_component = nullptr;

	AActor* actor_to_follow = nullptr;
	FVector relative_location_from_actor = FVector();
	
};
