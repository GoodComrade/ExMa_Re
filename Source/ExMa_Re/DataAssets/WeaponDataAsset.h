// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAssets/ItemDataAsset.h"
#include "Engine/SkeletalMesh.h"
#include "Animation/AnimBlueprint.h"
#include "WeaponDataAsset.generated.h"

class AWeaponActor;

UCLASS(BlueprintType, Blueprintable)
class EXMA_RE_API UWeaponDataAsset : public UItemDataAsset
{
	GENERATED_BODY()
	
public:
	UWeaponDataAsset(const FObjectInitializer& ObjectInitializer);

	virtual UItemObject* ConstructItemInstance() override;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AWeaponActor> WeaponActorClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	USkeletalMesh* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAnimBlueprint* MeshABP;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTagContainer WeaponType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTagContainer DamageType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	float Damage = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	int32 AttackCost = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	double Cooldown = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	double ShootDelay = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	double ReloadTime = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	int32 Spread = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	int32 MaxBulletsCount = -1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	int32 CurrenMagazineCapacity = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	int32 MaxMagazineCapacity = 0;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	//int32 BurstSize = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	int32 MinRange = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	int32 MaxRange = 0;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	//int32 MinBulletsInShot = 0;
	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	//int32 MaxBulletsInShot = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	int32 Health = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly);
	int32 AimTime = 0;
};
