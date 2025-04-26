// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/ItemDataAsset.h"
#include "Engine/SkeletalMesh.h"
#include "Animation/AnimBlueprint.h"
#include "WeaponDataAsset.generated.h"

class AWeaponActor;
class UGameplayAbility;

UCLASS(BlueprintType, Blueprintable)
class EXMA_RE_API UWeaponDataAsset : public UItemDataAsset
{
	GENERATED_BODY()
	
public:
	UWeaponDataAsset(const FObjectInitializer& ObjectInitializer);

	virtual UItemObject* ConstructItemInstance() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AWeaponActor> WeaponActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USkeletalMesh* WeaponMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimBlueprint* MeshABP;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayAbility> FireAbility;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayAbility> ReloadAbility;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* FireMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* ReloadMontage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTagContainer WeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTagContainer DamageType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	float Damage = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	int32 AttackCost = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	double Cooldown = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	double ShootDelay = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	double ReloadTime = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	int32 Spread = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	int32 MaxBulletsCount = -1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	int32 CurrenMagazineCapacity = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	int32 MaxMagazineCapacity = 0;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	//int32 BurstSize = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	int32 MinRange = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	int32 MaxRange = 0;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	//int32 MinBulletsInShot = 0;
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	//int32 MaxBulletsInShot = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	int32 Health = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	int32 MaxHealth = 0;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	//double BurstDelay = 0;
	//
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	//TArray<int32> ProjectileSpeed;
	//
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	//int32 ProjectileGravityMultiplier = 0;
	//
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	//int32 AimType = 0;
	//
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	//int32 BlustRadius = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly);
	int32 AimTime = 0;
};
