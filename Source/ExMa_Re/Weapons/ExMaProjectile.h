// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayEffectTypes.h"
#include "Abilities/GameplayAbility.h"
#include "GameFramework/Actor.h"
#include "PhysicsEngine/RadialForceComponent.h"
#include "ExMaProjectile.generated.h"

//USTRUCT(BlueprintType)
//struct FProjectileProperties
//{
//    GENERATED_BODY()
//
//public:
//    UPROPERTY(BlueprintReadWrite, EditAnywhere)
//    float Range = 0;
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere)
//    float Speed = 0;
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere)
//    float MaxHeight = 0;
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere)
//    float Damage = 0;
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere)
//    float GravityScale = 0;
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere)
//    float BlustRadius = 0;
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere)
//    FVector StartLocation = FVector::ZeroVector;
//
//    UPROPERTY(BlueprintReadWrite, EditAnywhere)
//    FVector TargetLocation = FVector::ZeroVector;
//};

UCLASS()
class EXMA_RE_API AExMaProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AExMaProjectile();

    //virtual void SetProjectileParams(FProjectileProperties InProjectileProperties);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    UFUNCTION()
    virtual void OnSphereOverlapCharacter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION(BlueprintCallable)
    void ApplyEffectsToTarget(UAbilitySystemComponent* Target);

    UFUNCTION(BlueprintCallable)
    void ApplyBlustEffect(FVector Location);

    //UFUNCTION()
    //void OnProjectileHit();
    //
    //UFUNCTION()
    //void DestroyEffect();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
    UPROPERTY(BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
    TArray<FGameplayEffectSpecHandle> TargetGrantedEffects;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    class UProjectileMovementComponent* ProjectileMovementComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    class UCapsuleComponent* CollisionCapsule;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FVector TargetLocation;

    //TODO: Maybe will need to implement explosion damage
    //UPROPERTY(BlueprintReadOnly, Meta = (ExposeOnSpawn))
    //TArray<FAreaEffectSpec> TargetAreaEffectsSpec;

    UPROPERTY(BlueprintReadWrite)
    class AWeaponActor* Weapon;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    FName BlustVFXRowName;

protected:
    //UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    //FProjectileProperties ProjectileProperties;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    URadialForceComponent* RadialForceComponent;

    UPROPERTY(BlueprintReadOnly)
    int32 CurrentEnemyHitCount = 0;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    bool bDestroyOnArrivedTargetLocation = false;
};
