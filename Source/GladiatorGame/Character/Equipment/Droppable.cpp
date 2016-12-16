#include "GladiatorGame.h"
#include "Droppable.h"
#include "UnrealNetwork.h"

// Sets default values
ADroppable::ADroppable()
{
	PrimaryActorTick.bCanEverTick = true;

	this->hitbox = Cast<UPrimitiveComponent>(CreateDefaultSubobject<UBoxComponent>(TEXT("hitbox")));
	this->mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("mesh"));
	
	this->mesh->SetNetAddressable();
	this->mesh->SetIsReplicated(true);
}

void ADroppable::Init(USkeletalMeshComponent* mesh_component)
{
	mesh->SetSkeletalMesh(mesh_component->SkeletalMesh);

	mesh->RegisterComponent();
	mesh->Activate();

	hitbox->RegisterComponent();
	hitbox->Activate();

	mesh->SnapTo(hitbox);

	Cast<UBoxComponent>(hitbox)->SetBoxExtent(mesh_component->SkeletalMesh->GetImportedBounds().BoxExtent * .5f);
	hitbox->SetCollisionProfileName(TEXT("Droppable"));
	mesh->SetCollisionProfileName(TEXT("Droppable"));

	hitbox->SetSimulatePhysics(true);
	hitbox->SetHiddenInGame(true);

	this->SetActorLocation(mesh_component->GetComponentLocation());
	hitbox->SetWorldTransform(mesh_component->GetComponentTransform());

	mesh_component->SetVisibility(false);
}

void ADroppable::ApplyForces(FVector force, FVector torque)
{
	if (hitbox)
	{
		hitbox->SetPhysicsLinearVelocity(force);
		hitbox->SetAllPhysicsAngularVelocity(torque);
	}
}

bool ADroppable::IsSameAs(USkeletalMeshComponent* base)
{
	if (mesh->SkeletalMesh == base->SkeletalMesh)
		return true;

	return false;
}

FVector ADroppable::GetPhysicalizedPosition()
{
	if (hitbox)
		return hitbox->GetComponentLocation();
	else
		return this->GetActorLocation();
}

UPrimitiveComponent* ADroppable::GetHitbox()
{
	return this->hitbox;
}
