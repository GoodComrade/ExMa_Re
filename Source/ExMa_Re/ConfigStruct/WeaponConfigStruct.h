#pragma once

#include "ExMa_Re/Enums/WeaponType.h"
#include "ExMa_Re/Enums/WeaponDamageType.h"
#include "ExMa_Re/DataAssets/WeaponDataAsset.h"
#include "Engine/SkeletalMesh.h"
#include "Animation/AnimBlueprint.h"
#include "GameplayTagContainer.h"
#include "WeaponConfigStruct.generated.h"

USTRUCT(BlueprintType)
struct FWeaponConfigStruct : public FTableRowBase
{
    GENERATED_USTRUCT_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    USkeletalMesh* WeaponMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    UAnimBlueprint* MeshABP;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "WeaponData"))
    UWeaponDataAsset* WeaponData;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "WeaponType"))
    FGameplayTagContainer WeaponType;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "DamageType"))
    FGameplayTagContainer DamageType;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Damage"))
    float Damage = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "AttackCost"))
    int32 AttackCost = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Cooldown"))
    double Cooldown = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ShootDelay"))
    double ShootDelay = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ReloadTime"))
    double ReloadTime = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Spread"))
    int32 Spread = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "MaxBulletsCount"))
    int32 MaxBulletsCount = -1;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "MagazineSize"))
    int32 MagazineSize = 0;

    //UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "BurstSize"))
    //int32 BurstSize = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "MinRange"))
    int32 MinRange = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "MaxRange"))
    int32 MaxRange = 0;

    //UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "MinBulletsInShot"))
    //int32 MinBulletsInShot = 0;
    //
    //UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "MaxBulletsInShot"))
    //int32 MaxBulletsInShot = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "MaxHealth"))
    int32 MaxHealth = 0;

    //UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "BurstDelay"))
    //double BurstDelay = 0;

    //UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ProjectileSpeed"))
    //TArray<int32> ProjectileSpeed;
    //
    //UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ProjectileGravityMultiplier"))
    //int32 ProjectileGravityMultiplier = 0;
    //
    //UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "AimType"))
    //int32 AimType = 0;
    //
    //UPROPERTY(BlueprintReadWrite, EditAnywhere)
    //int32 BlustRadius = 0;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "AimTime"))
    int32 AimTime = 0;
};