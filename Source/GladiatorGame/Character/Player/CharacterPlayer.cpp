// Fill out your copyright notice in the Description page of Project Settings.

#include "GladiatorGame.h"
#include "GladiatorGameController.h"
#include "CharacterPlayer.h"
#include "Animation/SkeletalMeshActor.h"
#include "GladiatorGameState.h"

class AAICharacter : public ABaseCharacter{};

// --- ----- --- //

#pragma region Default Functions

ACharacterPlayer::ACharacterPlayer()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACharacterPlayer::BeginPlay()
{
	Super::BeginPlay();
	FindCamera();
}

void ACharacterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	this->UpdateLock(this->lockTarget);
}

bool ACharacterPlayer::AttackEnd()
{
	this->isAttacking = false;
	if (this->lockTarget)
	{
		this->UpdateEnemyMap();
		this->SortEnemyMap();
		this->lockTarget = this->FindForwardTarget();
	}
	return true;
}

void ACharacterPlayer::Death()
{
	Cast<AGladiatorGameState>(GetWorld()->GetGameState())->AIWin();
}


#pragma endregion

// --- ----- --- //

#pragma region Inputs

void ACharacterPlayer::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	InputComponent->BindAxis("ViewVertical", this, &ACharacterPlayer::VerticalAxis);
	InputComponent->BindAxis("ViewHorizontal", this, &ACharacterPlayer::HorizontalAxis);

	InputComponent->BindAxis("MoveVertical", this, &ACharacterPlayer::VerticalMovement);
	InputComponent->BindAxis("MoveHorizontal", this, &ACharacterPlayer::HorizontalMovement);

	InputComponent->BindAxis("LockSwitch", this, &ACharacterPlayer::SwitchTarget);

	InputComponent->BindAction("Attack", IE_Pressed, this, &ACharacterPlayer::Attack);
	InputComponent->BindAction("Lock", IE_Pressed, this, &ACharacterPlayer::CallLock);
	InputComponent->BindAction("Interact", IE_Pressed, this, &ACharacterPlayer::TryPickEquipment);

	InputComponent->BindAction("OpenMenu", IE_Pressed, this, &ACharacterPlayer::DisplayNetworkMenu).bExecuteWhenPaused = true;
}

void ACharacterPlayer::VerticalAxis(float value)
{
	float rotation = value * sensitivity * GetWorld()->GetDeltaSeconds();
	AddControllerPitchInput(rotation);
}

void ACharacterPlayer::HorizontalAxis(float value)
{
	float rotation = value * sensitivity * GetWorld()->GetDeltaSeconds();
	AddControllerYawInput(rotation);
}

void ACharacterPlayer::VerticalMovement(float value)
{
	if (isAttacking || _Life <= 0)
		return;

	FRotator cur_rotator;
	if (!this->lockTarget)
		cur_rotator = GetControlRotation();
	else
	{
		FVector2D lookatdir = (FVector2D(this->lockTarget->GetActorLocation()) - FVector2D(this->GetActorLocation())).GetSafeNormal();
		cur_rotator = FRotationMatrix::MakeFromX(FVector(lookatdir, 0.f)).ToQuat().Rotator();
	}

	cur_rotator.Pitch = 0.0f;
	FVector dir_vector = cur_rotator.Vector();
	AddMovementInput(dir_vector, value * speed * GetWorld()->GetDeltaSeconds());
}

void ACharacterPlayer::HorizontalMovement(float value)
{
	if (isAttacking || _Life == 0)
		return;

	FRotator cur_rotator;
	if (!this->lockTarget)
		cur_rotator = GetControlRotation();
	else
	{
		FVector2D lookatdir = (FVector2D(this->lockTarget->GetActorLocation()) - FVector2D(this->GetActorLocation())).GetSafeNormal();
		cur_rotator = FRotationMatrix::MakeFromX(FVector(lookatdir, 0.f)).ToQuat().Rotator();
	}

	cur_rotator.Pitch = 0.0f;
	FVector dir_vector = cur_rotator.RotateVector(FVector::RightVector.RotateAngleAxis(180.f, FVector::UpVector));
	AddMovementInput(dir_vector, value * speed * GetWorld()->GetDeltaSeconds());
}


#pragma endregion

// --- ----- --- //

#pragma region Camera Control

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

#pragma region LockSystem

void ACharacterPlayer::CallLock()
{
	if (this->lockTarget == nullptr)
	{
		this->UpdateEnemyMap();
		this->SortEnemyMap();
		this->lockTarget = this->FindForwardTarget();
	}
	else
		this->lockTarget = nullptr;

}

void ACharacterPlayer::UpdateLock(AActor* target)
{
	FVector pos;
	if (target == nullptr)
		return;
	else
		pos = target->GetActorLocation();

	FVector axis = this->cameraComponent->GetRightVector();
	DrawDebugCircle(GetWorld(), pos, 100.f, 64, FColor::Red, false, -1.f, 0.f, 10.f, axis, this->cameraComponent->GetUpVector(), false);

	FVector2D lookatdir = FVector2D(pos) - FVector2D(this->GetActorLocation());
	
	FQuat rot =  FQuat::Slerp(this->GetActorQuat(), FRotationMatrix::MakeFromX(FVector(lookatdir, 0.f)).ToQuat(), .1f);
	this->SetActorRotation(rot);
}

TMap<float, AActor*> ACharacterPlayer::UpdateEnemyMap()
{
	this->enemy_map.Empty();

	for (TActorIterator<AAICharacter> enemy(GetWorld()); enemy; ++enemy)
	{
		AAICharacter* current = *enemy;
		if (current->GetClass() != this->GetClass() && current->_Life > 0)
		{
			AActor* cur_actor = Cast<AActor>(current);
			this->enemy_map.Add(this->GetActorPositionFactor(cur_actor), cur_actor);
		}
	}

	return this->enemy_map;
}

void ACharacterPlayer::SortEnemyMap()
{
	TMap< float, AActor*> raw = TMap< float, AActor*>();
	TArray<float> factors = TArray<float>();

	TArray<float> keys = TArray<float>();
	this->enemy_map.GetKeys(keys);

	for (float key : keys)
	{
		float curfactor = this->GetActorPositionFactor(enemy_map[key]);
		raw.Add(curfactor, enemy_map[key]);
		factors.Add(curfactor);
	}

	factors.Sort();
	this->enemy_map.Empty();

	for (float f : factors)
		this->enemy_map.Add(f, raw[f]);
}

float ACharacterPlayer::GetActorPositionFactor(AActor* factorized)
{
	FVector dir = factorized->GetActorLocation() - this->GetActorLocation();
	float raw = ACharacterPlayer::GetAngleBetween(dir, this->GetActorForwardVector());
	float ref = raw * this->GetLRFactor(this, factorized);
	return ref;
}

AActor* ACharacterPlayer::FindForwardTarget()
{
	
	TArray<float> keys = TArray<float>();
	this->enemy_map.GetKeys(keys);

	for (float ikey : keys)
	{
		bool isMin = true;
		for (float jkey : keys)
		{
			if (ikey == jkey)
				continue;
			if (FMath::Abs(ikey) > FMath::Abs(jkey))
			{
				isMin = false;
				break;
			}
		}
		if (!isMin)
			continue;
		else
			return enemy_map[ikey];
	}

	return nullptr;
}

void ACharacterPlayer::SwitchTarget(float value)
{
	if (isAttacking || !this->lockTarget)
		return;

	int factor = FMath::Sign(value);

	TArray<float> keys = TArray<float>();
	enemy_map.GetKeys(keys);
	float curkey = *enemy_map.FindKey(this->lockTarget);

	int idx = keys.IndexOfByKey(curkey) + factor;
	if (idx >= keys.Num())
		idx = 0;
	else if (idx < 0)
		idx = keys.Num() - 1;

	this->lockTarget = enemy_map[keys[idx]];
}

#pragma endregion

// --- ----- --- //

#pragma region Utilities

float ACharacterPlayer::GetAngleBetween(FVector V1, FVector V2)
{
	return FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(V1.GetSafeNormal(), V2.GetSafeNormal())));
}

int ACharacterPlayer::GetLRFactor(AActor* ref_actor, AActor* tested_actor)
{
	FVector refpos = ref_actor->GetActorLocation();
	FVector testpos = tested_actor->GetActorLocation();

	float LDist = FVector::Dist(refpos - ref_actor->GetActorRightVector(), testpos);
	float RDist = FVector::Dist(refpos + ref_actor->GetActorRightVector(), testpos);

	if (LDist < RDist)
		return LFACTOR;
	else if (RDist < LDist)
		return RFACTOR;

	return 0;
}

#pragma endregion 

// --- ----- --- //

void ACharacterPlayer::DisplayNetworkMenu()
{
	Cast<AGladiatorGameController>(GetController())->DisplayNetworkMenu();
}