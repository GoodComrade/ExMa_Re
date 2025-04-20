// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/WeaponDataAsset.h"

#include "ExMa_re/Items/WeaponItemObject.h"
#include "ExMa_re/Items/WeaponActor.h"

UWeaponDataAsset::UWeaponDataAsset(const FObjectInitializer& ObjectInitializer) : UItemDataAsset(ObjectInitializer)
{
	ItemObjectClass = UWeaponItemObject::StaticClass();
	WeaponActorClass = AWeaponActor::StaticClass();
}

UItemObject* UWeaponDataAsset::ConstructItemInstance()
{
	UWeaponItemObject* WeaponObject = NewObject<UWeaponItemObject>(this, ItemObjectClass);
	WeaponObject->SetItemData(this);

	return WeaponObject;
}
