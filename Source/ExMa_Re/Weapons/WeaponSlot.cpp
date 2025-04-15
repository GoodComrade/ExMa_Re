// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/WeaponSlot.h"

void UWeaponSlot::SetSlotDimensions(FTileStruct DimentionsToSet)
{
	SlotDimentions = DimentionsToSet;
}

bool UWeaponSlot::TryAddWeapon(UWeaponItemObject* WeaponToSet)
{
	if (IsDimentionsMatching(WeaponToSet, SlotDimentions) && HasWeaponInSlot() == false)
	{
		AddWeaponInSlot(WeaponToSet);
		return true;
	}

	return false;
}

void UWeaponSlot::AddWeaponInSlot(UWeaponItemObject* WeaponToSet)
{
	if (WeaponToSet->IsRotated())
		WeaponToSet->Rotate();

	InstalledWeapon = WeaponToSet;

	OnWeaponSlotChanged.Broadcast();
}

void UWeaponSlot::RemoveWeaponFromSlot(UWeaponItemObject* WeaponToRemove)
{
	if (WeaponToRemove == NULL)
		return;

	InstalledWeapon = nullptr;

	OnWeaponSlotChanged.Broadcast();
}

bool UWeaponSlot::IsDimentionsMatching(UWeaponItemObject* WeaponToCheck, FTileStruct SlotSize)
{
	if(WeaponToCheck->IsRotated())
		return (SlotSize.X == WeaponToCheck->GetDimentions().Y && SlotSize.Y == WeaponToCheck->GetDimentions().X) ? true : false;

	return (SlotSize.X == WeaponToCheck->GetDimentions().X && SlotSize.Y == WeaponToCheck->GetDimentions().Y) ? true : false;
}

bool UWeaponSlot::HasWeaponInSlot()
{
	return InstalledWeapon != nullptr ? true : false;
}

