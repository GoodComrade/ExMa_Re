#pragma once

#include "ExMa_Re/Enums/ItemType.h"
#include "ExMa_Re/Enums/WeaponType.h"
#include "ExMa_Re/Enums/WeaponDamageType.h"
#include "GameplayTagContainer.h"
#include "ItemInfoStruct.generated.h"

USTRUCT(BlueprintType)
struct FItemInfoStruct
{
    GENERATED_USTRUCT_BODY()

public:

#pragma region ItemInfo
	UPROPERTY(EditAnywhere, meta = (DisplayName = "Name"))
	FText Name;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Description"))
	FText Description;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ItemType"))
	FGameplayTagContainer ItemType;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Weight"))
	int Weight = 0;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Cost"))
	int Cost = 0;
#pragma endregion BaseInfo

#pragma region ItemInfo
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "WeaponType"))
	FGameplayTagContainer WeaponType;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "DamageType"))
	FGameplayTagContainer DamageType;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Damage"))
	int Damage = 0;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "AttackCost"))
	int AttackCost = 0;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Cooldown"))
	int Cooldown = 0;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "ShootDelay"))
	int ShootDelay = 0;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "FireRate"))
	double FireRate = 0;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "FireDistance"))
	int FireDistance = 0;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "FireSpread"))
	int FireSpread = 0;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "CurrenMagazineCapacity"))
	int CurrenMagazineCapacity = 0;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "MaxMagazineCapacity"))
	int MaxMagazineCapacity = 0;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "ReloadTime"))
	int ReloadTime = 0;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "CurrentToughness"))
	int CurrentToughness = 0;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "MaxToughness"))
	int MaxToughness = 0;
#pragma endregion WeaponInfo
};

