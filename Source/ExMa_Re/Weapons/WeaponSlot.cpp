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

void UWeaponSlot::InitWeaponSlot(AActor* OwnerToSet, FTileStruct DimentionsToSet, FName SocketNameToSet)
{
	if (OwnerToSet == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UWeaponSlot::InitWeaponSlot: OwnerToSet IS nullptr!"));
		return;
	}

	if (SocketNameToSet.IsNone())
	{
		UE_LOG(LogTemp, Error, TEXT("UWeaponSlot::InitWeaponSlot: SocketNameToSet IS NONE!"));
		return;
	}

	SetSlotOwner(OwnerToSet);
	SetSlotSocketName(SocketNameToSet);
	SetSlotDimensions(DimentionsToSet);

	InitWeaponActor();
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

void UWeaponSlot::InitWeaponActor()
{
	AExMa_RePawn* PlayerPawn = Cast<AExMa_RePawn>(SlotOwner);
	if (!PlayerPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("UWeaponSlot::AddWeaponInSlot: PlayerPawn IS NULLPTR!"));
		return;
	}

	AWeaponActor* WeaponActor = PlayerPawn->GetGameState()->SpawnWeaponActor(SlotOwner, SlotSocket);
	if (!WeaponActor)
	{
		UE_LOG(LogTemp, Error, TEXT("UWeaponSlot::AddWeaponInSlot: WeaponActor IS NULLPTR!"));
		return;
	}

	InstalledWeaponActor = WeaponActor;
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
	if (WeaponToSet == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UWeaponSlot::AddWeaponInSlot: WeaponToSet IS NULLPTR!"));
		return;
	}

	UWeaponDataAsset* WeaponData = Cast<UWeaponDataAsset>(WeaponToSet->GetItemData());

	if (!WeaponData)
	{
		UE_LOG(LogTemp, Error, TEXT("UWeaponSlot::AddWeaponInSlot: WeaponData IS NULLPTR!"));
		return;
	}

	if (InstalledWeapon)
		ReturnWeaponObjectToInventory();

	if (WeaponToSet->IsRotated())
		WeaponToSet->Rotate();

	InstalledWeapon = WeaponToSet;
	InstalledWeapon->SetItemOwner(SlotOwner);

	InstalledWeaponActor->SetWeaponData(WeaponData);
	InstalledWeaponActor->SetWeaponOwner(SlotOwner);
	InstalledWeaponActor->SetWeaponParamsFromData();

	InstalledWeaponActor->EnableAbilities();

	OnWeaponSlotChanged.Broadcast();
}

void UWeaponSlot::RemoveWeaponFromSlot(UWeaponItemObject* WeaponToRemove)
{
	if (WeaponToRemove == NULL)
		return;

	InstalledWeapon = nullptr;

	InstalledWeaponActor->RemoveWeaponParams();
	InstalledWeaponActor->DisableAbilities();

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

void UWeaponSlot::SetFireGroupTag(FGameplayTag InFireGroupTag)
{
	FireGroupTag = InFireGroupTag;
}

void UWeaponSlot::SetSlotSocketName(FName SocketName)
{
	SlotSocket = SocketName;
}

void UWeaponSlot::SetWeaponActor()
{
	//call spawn weapon actor from game state & set returned value to InstalledWeaponActor;
}

void UWeaponSlot::ReturnWeaponObjectToInventory()
{
	AExMa_RePawn* OwnerPawn = Cast<AExMa_RePawn>(SlotOwner);
	if (!OwnerPawn)
	{
		UE_LOG(LogTemp, Error, TEXT("UWeaponSlot::AddWeaponInSlot: OwnerPawn IS NULLPTR!"));
		return;
	}

	OwnerPawn->AddItemObjectToInventory(InstalledWeapon);
	InstalledWeapon = nullptr;
}

bool UWeaponSlot::IsSlotAvaliable(UWeaponItemObject* InWeapon, FTileStruct SlotSize)
{
	return IsDimentionsMatching(InWeapon, SlotSize)/* && HasWeaponInSlot() == false*/;
}

