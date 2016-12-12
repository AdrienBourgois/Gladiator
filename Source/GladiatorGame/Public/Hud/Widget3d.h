#pragma once

#include "Components/ActorComponent.h"
#include "WidgetComponent.h"
#include "Blueprint/UserWidget.h"
#include "WidgetInterface.h"
#include "Widget3d.generated.h"

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
	void Follow(TSubclassOf<UUserWidget> _type, int init_value = 0, FVector _relative_location = FVector(0.f, 0.f, 100.f), bool _fly_animation = false);
	UFUNCTION(BlueprintCallable, Category = "C++ Function")
	void Action(int value) const;

	void Destruct();

	UUserWidget* widget_instance = nullptr;
	UWidgetComponent* widget_component = nullptr;

	AActor* actor_to_follow = nullptr;
	FVector relative_location_from_actor = FVector();

	APlayerCameraManager* camera_manager = nullptr;

	bool fly_animation = false;
	FVector current_fly_location = FVector();
	const float max_z_fly = 50.f;
	
};
