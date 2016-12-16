// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "HUD/LifeBar.h"
//DEBUG
#include "Public/Hud/Widget3d.h"
#include "BaseCharacter.generated.h"

/**
 * 
 */

const float ONE_METER = 100.f;
class AAIDirector;

UCLASS(Blueprintable)
class GLADIATORGAME_API ABaseCharacter : public ACharacter
{
    GENERATED_BODY()
public:
    ABaseCharacter();
    ABaseCharacter(int Life);
    virtual ~ABaseCharacter();
    
    virtual void BeginPlay();

    virtual void Attack();
    virtual void ReceiveDamage(int dmg = 1);
    UFUNCTION(BlueprintCallable, Category = "Character Management") virtual void Death();
    virtual void Move();

    UFUNCTION(BlueprintCallable, Category = "Character Attack") virtual bool HammerHit();
    UFUNCTION(BlueprintCallable, Category = "Character Attack") virtual bool AttackEnd();

    virtual void GetLifetimeReplicatedProps(TArray < FLifetimeProperty > & OutLifetimeProps) const;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Replicated) int _Life = 5;
    void SetLife(int Life);
    UFUNCTION(reliable, server, WithValidation)
        void ServSetLife(int Life);
        void ServSetLife_Implementation(int Life);
        bool ServSetLife_Validate(int Life);

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated) bool isAttacking = false;
    void SetIsAttacking(bool bNewSomeBool);
    UFUNCTION(reliable, server, WithValidation)
        void ServSetIsAttacking(bool bNewSomeBool);
        void ServSetIsAttacking_Implementation(bool bNewSomeBool);
        bool ServSetIsAttacking_Validate(bool bNewSomeBool);

    UPROPERTY(Replicated) bool HammerVisible = true;
    void SetHammerVisible(bool bNewSomeBool);
    UFUNCTION(reliable, NetMulticast, WithValidation)
        void ServSetHammerVisible(bool bNewSomeBool);
        void ServSetHammerVisible_Implementation(bool bNewSomeBool);
        bool ServSetHammerVisible_Validate(bool bNewSomeBool);

    UPROPERTY(Replicated) bool ShieldVisible = true;
    void SetShieldVisible(bool bNewSomeBool);
    UFUNCTION(reliable, NetMulticast, WithValidation)
        void ServSetShieldVisible(bool bNewSomeBool);
        void ServSetShieldVisible_Implementation(bool bNewSomeBool);
        bool ServSetShieldVisible_Validate(bool bNewSomeBool);

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    UWidget3d* lifeBarHandler = nullptr;
    TSubclassOf<UUserWidget> life_bar_class;
    TSubclassOf<UUserWidget> damage_text_class;

    UPROPERTY(EditAnywhere) float dropRate = .5f;
    UPROPERTY(EditAnywhere) float pickRadius = 100.f;

    UPROPERTY(EditAnywhere)
    UClass* DroppableBP;

    USceneComponent* weaponRef = nullptr;
    USceneComponent* shieldRef = nullptr;

    UPROPERTY(EditAnywhere) USkeletalMesh* weaponMeshRef = nullptr;
    UPROPERTY(EditAnywhere) USkeletalMesh* shieldMeshRef = nullptr;

    TMap<USceneComponent*, bool> equipment = TMap<USceneComponent*, bool>();

    void InitEquipmentMap();

    void RandomDrop();
    
    virtual void TryPickEquipment();
    void PickEquipment(AActor* picked);

    AActor* DropEquipment(USceneComponent* toDrop);

    AAIDirector* AImgr;
};