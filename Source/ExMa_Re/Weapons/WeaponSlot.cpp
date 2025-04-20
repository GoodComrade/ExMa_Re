// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/WeaponSlot.h"
#include "Templates/Tuple.h"
#include "ExMa_Re/Structs/TileStruct.h"
#include "ExMa_Re/Vehicles/ExMa_RePawn.h"
#include "ExMa_Re/Game/ExMa_GameState.h"
#include "ExMa_Re/Items/WeaponActor.h"
#include "Kismet/GameplayStatics.h"

FWeaponSlotStruct UWeaponSlot::GetWeaponObjectAtSlot() const
{
	if (InstalledWeapon == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UWeaponSlot:: InstalledWeapon IS NULLPTR!"));
		return FWeaponSlotStruct();
	}

	FTileStruct InstallenWeaponTileStruct = FTileStruct(InstalledWeapon->GetDimentions().X, InstalledWeapon->GetDimentions().Y);

	return FWeaponSlotStruct(InstalledWeapon, InstallenWeaponTileStruct);
}

void UWeaponSlot::SetSlotOwner(AActor* OwnerToSet)
{
	if (OwnerToSet == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UWeaponSlot::SetSlotOwner: OwnerToSet IS nullptr!"));
		return;
	}

	SlotOwner = OwnerToSet;
}

void UWeaponSlot::SetSlotDimensions(FTileStruct DimentionsToSet)
{
	SlotDimentions = DimentionsToSet;
}

bool UWeaponSlot::TryAddWeapon(UWeaponItemObject* WeaponToSet)
{
	if (IsSlotAvaliable(WeaponToSet, SlotDimentions))
	{
		AddWeaponInSlot(WeaponToSet);
		return true;
	}

	return false;
}

void UWeaponSlot::AddWeaponInSlot(UWeaponItemObject* WeaponToSet)
{
	AExMa_RePawn* PlayerPawn = Cast<AExMa_RePawn>(SlotOwner);
	if (!PlayerPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("UWeaponSlot::AddWeaponInSlot: PlayerPawn IS NULLPTR!"));
		return;
	}
	
	

	if (WeaponToSet->IsRotated())
		WeaponToSet->Rotate();

	InstalledWeapon = WeaponToSet;
	InstalledWeapon->SetItemOwner(SlotOwner);

	AWeaponActor* WeaponActor = PlayerPawn->GetGameState()->SpawnWeaponActor(InstalledWeapon, SlotOwner, SlotSocket);
	if (!WeaponActor)
	{
		UE_LOG(LogTemp, Error, TEXT("UWeaponSlot::AddWeaponInSlot: WeaponActor IS NULLPTR!"));
		return;
	}

	InstalledWeaponActor = WeaponActor;

	OnWeaponSlotChanged.Broadcast();
}

void UWeaponSlot::RemoveWeaponFromSlot(UWeaponItemObject* WeaponToRemove)
{
	if (WeaponToRemove == NULL)
		return;

	InstalledWeapon = nullptr;

	InstalledWeaponActor->Destroy();
	InstalledWeaponActor = nullptr;

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

void UWeaponSlot::SetSlotSocketName(FName SocketName)
{
	SlotSocket = SocketName;
}

void UWeaponSlot::SetWeaponActor()
{
	//call spawn weapon actor from game state & set returned value to InstalledWeaponActor;
}

bool UWeaponSlot::IsSlotAvaliable(UWeaponItemObject* InWeapon, FTileStruct SlotSize)
{
	return IsDimentionsMatching(InWeapon, SlotSize) && HasWeaponInSlot() == false;
}

