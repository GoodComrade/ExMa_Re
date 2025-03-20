// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/WeaponItemObject.h"
#include "ExMa_Re/Enums/WeaponType.h"
#include "ExMa_Re/Enums/WeaponDamageType.h"
#include "ExMa_Re/Items/ItemInfoStruct.h"
#include "ExMa_Re/Weapons/ExMa_WeaponAttributes.h"

UWeaponItemObject::UWeaponItemObject()
{
	WeaponType = EWeaponType::None;
	DamageType = EWeaponDamageType::None;

}

void UWeaponItemObject::SetWeaponType(EWeaponType NewWeaponType)
{
	WeaponType = NewWeaponType;
}

void UWeaponItemObject::SetWeaponDamageType(EWeaponDamageType NewDamageType)
{
	DamageType = NewDamageType;
}

void UWeaponItemObject::SetItemInfo()
{
	Super::SetItemInfo();

	UWeaponDataAsset* WeaponData = Cast<UWeaponDataAsset>(ItemData);

	if (WeaponData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UWeaponItemObject:: WeaponData is nullptr"));
		return;
	}

	ItemInfo.WeaponType = WeaponData->WeaponType;
	ItemInfo.DamageType = WeaponData->DamageType;
	ItemInfo.Damage = WeaponData->Damage;
	ItemInfo.FireRate = CalculateEffectiveRPM(WeaponData->ShootDelay, WeaponData->MaxMagazineCapacity, WeaponData->ReloadTime);
	ItemInfo.FireDistance = WeaponData->MaxRange;
	ItemInfo.FireSpread = WeaponData->Spread;
	ItemInfo.CurrenMagazineCapacity = WeaponData->CurrenMagazineCapacity;
	ItemInfo.MaxMagazineCapacity = WeaponData->MaxMagazineCapacity;
	ItemInfo.ReloadTime = WeaponData->ReloadTime;
	ItemInfo.CurrentToughness = WeaponData->Health;
	ItemInfo.MaxToughness = WeaponData->MaxHealth;

	UE_LOG(LogTemp, Warning, TEXT("UWeaponItemObject:: WeaponItemInfo Set"));
}

double UWeaponItemObject::CalculateEffectiveRPM(double ShootDelay, int MagazineSize, double ReloadTime)
{
	double EffectiveRPM = (60 * MagazineSize) / (MagazineSize * ShootDelay + ReloadTime);

	return EffectiveRPM;
}
