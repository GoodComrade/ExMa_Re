// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ExMa_WeaponSlotWidget.h"
#include "ExMa_Re/Vehicles/ExMa_RePawn.h"

#include "ExMa_Re/Game/ExMa_GameInstance.h"

void UExMa_WeaponSlotWidget::NativeConstruct()
{
}

void UExMa_WeaponSlotWidget::SetComponents(APlayerController* InPlayerController, UWeaponSlot* InWeaponSlotRef)
{
	if (InPlayerController == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UExMa_WeaponSlotWidget: InPlayerComponent IS NULL"));
		return;
	}

	PlayerController = InPlayerController;

	if (InWeaponSlotRef == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UExMa_WeaponSlotWidget: InventoryComponentRef IS NULL"));
		return;
	}

	UExMa_GameInstance* GameInstance = Cast<UExMa_GameInstance>(GetGameInstance());

	if (GameInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UExMa_WeaponSlotWidget:: GameInstance is NULLPTR!"));
		return;
	}
	
	WeaponSlotRef = InWeaponSlotRef;
	TileSize = GameInstance->TileSize;
}
