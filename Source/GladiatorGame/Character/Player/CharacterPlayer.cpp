// Fill out your copyright notice in the Description page of Project Settings.

#include "GladiatorGame.h"
#include "CharacterPlayer.h"

class AAICharacter : public ACharacter{};

// --- ----- --- //

#pragma region Default Functions

// Sets default values
ACharacterPlayer::ACharacterPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

void ACharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
	SetupInputs();
	FindCamera();
	len = FVector::Dist(this->cameraComponent->GetComponentLocation(), this->GetActorLocation());
}

void ACharacterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	this->DebugLock();

}

bool ACharacterPlayer::HammerHit()
{
	TArray<FOverlapResult> results;
	this->GetWorld()->OverlapMultiByChannel(results,
		this->GetActorLocation() + this->GetActorForwardVector() * 2,
		this->GetActorRotation().Quaternion(),
		ECollisionChannel::ECC_MAX,
		FCollisionShape::MakeSphere(100.f));

	//DrawDebugSphere(GetWorld(), this->GetActorLocation() + this->GetActorForwardVector() * 2, 100.f, 32, FColor::Blue, false, 5.f);

	for (int i = 0; i < results.Num(); ++i)
	{
		FOverlapResult hit = results[i];
		if (hit.Actor->GetClass()->IsChildOf(AAICharacter::StaticClass()))
		{
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, hit.Actor->GetName());
			DrawDebugCircle(GetWorld(), hit.Actor->GetActorLocation(), 100.f, 64, FColor::Red, false, 5.f, 0, 0, this->cameraComponent->GetRightVector());
		}

	}
	return true;
}

bool ACharacterPlayer::AttackEnd()
{
	this->isAttacking = false;
	InputComponent->BindAction("Attack", IE_Pressed, this, &ACharacterPlayer::Attack);
	return true;
}

#pragma endregion

// --- ----- --- //

#pragma region Inputs

void ACharacterPlayer::SetupInputs()
{
	InputComponent->BindAxis("ViewVertical", this, &ACharacterPlayer::VerticalAxis);
	InputComponent->BindAxis("ViewHorizontal", this, &ACharacterPlayer::HorizontalAxis);

	InputComponent->BindAxis("MoveVertical", this, &ACharacterPlayer::VerticalMovement);
	InputComponent->BindAxis("MoveHorizontal", this, &ACharacterPlayer::HorizontalMovement);

	InputComponent->BindAction("Attack", IE_Pressed, this, &ACharacterPlayer::Attack);
}

void ACharacterPlayer::VerticalAxis(float value)
{
	float rotation = value * sensitivity * GetWorld()->GetDeltaSeconds();
	AddControllerPitchInput(rotation);
	this->AdaptView();
}

void ACharacterPlayer::HorizontalAxis(float value)
{
	float rotation = value * sensitivity * GetWorld()->GetDeltaSeconds();
	AddControllerYawInput(rotation);
	this->AdaptView();
}

void ACharacterPlayer::VerticalMovement(float value)
{
	if (isAttacking)
		return;

	FRotator cur_rotator = GetControlRotation();
	cur_rotator.Pitch = 0.0f;
	FVector dir_vector = cur_rotator.Vector();
	AddMovementInput(dir_vector, value * speed * GetWorld()->GetDeltaSeconds());
	this->AdaptView();
}

void ACharacterPlayer::HorizontalMovement(float value)
{
	if (isAttacking)
		return;

	FRotator cur_rotator = GetControlRotation();
	cur_rotator.Pitch = 0.0f;
	FVector dir_vector = cur_rotator.RotateVector(FVector::RightVector.RotateAngleAxis(180.f, FVector::UpVector));
	AddMovementInput(dir_vector, value * speed * GetWorld()->GetDeltaSeconds());
	this->AdaptView();
}

void ACharacterPlayer::DebugLock(ACharacter* target)
{
	FVector pos;
	if (target == nullptr)
		pos = this->GetActorLocation();
	else
		pos = target->GetActorLocation();

	FVector axis = this->cameraComponent->GetRightVector();// .RotateAngleAxis(this->cameraComponent->GetComponentRotation().Pitch, this->GetActorRightVector());
	DrawDebugCircle(GetWorld(), pos, 100.f, 64, FColor::Red, false, -1.f, 0.f, 10.f, axis);

}

void ACharacterPlayer::Attack()
{
	if (isAttacking)
		return;

	this->isAttacking = true;
	InputComponent->ClearActionBindings();
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, "Attack Not Implemented Yet");

}

#pragma endregion

// --- ----- --- //

#pragma region Camera Control

bool ACharacterPlayer::IsTargetViewable()
{
	if (!this->HasActiveCameraComponent() || !this->FindCamera())
		return false;

	FVector pos = this->cameraComponent->GetComponentLocation();
	
	TArray<FHitResult> results = TArray<FHitResult>();
	GetWorld()->LineTraceMultiByChannel(results, pos, this->GetActorLocation(), ECollisionChannel::ECC_MAX);
	for (int i =0; i < results.Num(); ++i)
	{
		FHitResult hit = results[i];

		if (hit.Actor->GetClass()->IsChildOf(ACharacter::StaticClass()))
			continue;
		return false;
	}
	return true;
	
}

bool ACharacterPlayer::IsTargetInRange()
{
	FVector pos = this->cameraComponent->GetComponentLocation();
	FHitResult result = FHitResult();

	GetWorld()->LineTraceSingleByChannel(result, pos, this->GetActorLocation(), ECollisionChannel::ECC_WorldStatic);

	return (result.Distance >= minLen);
}

void ACharacterPlayer::AdaptView()
{
	if (IsTargetViewable())
	{
		CheckDistance(); //Waiting for fix
		return;
	}
	FVector pos = this->cameraComponent->GetComponentLocation();
	FHitResult result = FHitResult();

	GetWorld()->LineTraceSingleByChannel(result, pos, this->GetActorLocation(), ECollisionChannel::ECC_MAX);
	AdaptFromCollision(result.ImpactPoint);
}

void ACharacterPlayer::AdaptFromCollision(FVector collider)
{
	if (this->cameraComponent && FVector::Dist(collider, this->GetActorLocation()) >= minLen)
		this->cameraComponent->SetWorldLocation(collider);
}

void ACharacterPlayer::CheckDistance()
{
	float curdist = FVector::Dist(this->cameraComponent->GetComponentLocation(), this->GetActorLocation());
	if (curdist < len)
	{
		FVector dir = this->cameraComponent->GetComponentLocation() - this->GetActorLocation();
		
		if (curdist >= minLen)
		{
			float factor = FMath::SmoothStep(0.f, len, curdist);
			this->cameraComponent->SetWorldLocation(this->GetActorLocation() + (dir.GetSafeNormal() * len * factor));
		}
		else
		{
			dir = -this->Controller->GetControlRotation().Vector();
			this->cameraComponent->SetWorldLocation(this->GetActorLocation() + (dir.GetSafeNormal() * minLen * 2));
		}
	}

}

UCameraComponent* ACharacterPlayer::FindCamera()
{
	TInlineComponentArray<UCameraComponent*> Cameras;
	GetComponents<UCameraComponent>(Cameras);

	for (UCameraComponent* CameraComponent : Cameras)
		if (CameraComponent->bIsActive)
			this->cameraComponent = CameraComponent;

	return this->cameraComponent;
}

#pragma endregion

// --- ----- --- //
