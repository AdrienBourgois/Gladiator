

#pragma once

#include "GameFramework/Actor.h"
#include "Droppable.generated.h"

UCLASS()
class GLADIATORGAME_API ADroppable : public AActor
{
	GENERATED_BODY()
	
public:	
	
	ADroppable();

	void Init(USkeletalMeshComponent* mesh_component);

	void ApplyForces(FVector force = FVector::ZeroVector, FVector torque = FVector::ZeroVector);

	bool IsSameAs(USkeletalMeshComponent* base);

	FVector GetPhysicalizedPosition();
	UPrimitiveComponent* GetHitbox();

private:

	UPrimitiveComponent* hitbox = nullptr;
	USkeletalMeshComponent* mesh = nullptr;
	
};
