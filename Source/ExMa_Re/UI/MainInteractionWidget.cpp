// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainInteractionWidget.h"

void UMainInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UMainInteractionWidget::SetPlayerController(APlayerController* InPlayerController)
{
	if (InPlayerController == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UMainInteractionWidget: InPlayerComponent IS NULL"));
		return;
	}
	PlayerController = InPlayerController;
}

void UMainInteractionWidget::SetInventoryComponentRef(UInventoryComponent* InInventoryComponentRef)
{
	if (InInventoryComponentRef == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UMainInteractionWidget: InventoryComponentRef IS NULL"));
		return;
	}
	InventoryComponentRef = InInventoryComponentRef;
}

void UMainInteractionWidget::SetOutInventoryComponentRef(UInventoryComponent* InOutInventoryComponentRef)
{
	if (InOutInventoryComponentRef == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UMainInteractionWidget: OutInventoryComponentRef IS NULL"));
		return;
	}
	OutInventoryComponentRef = InOutInventoryComponentRef;
}

void UMainInteractionWidget::SetWeaponComponentRef(UWeaponComponent* InWeaponComponenttRef)
{
	if (InWeaponComponenttRef == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UMainInteractionWidget: WeaponComponenttRef IS NULL"));
		return;
	}
	WeaponComponentRef = InWeaponComponenttRef;

	WeaponComponentRef->OnWeaponSlotCreated.AddDynamic(this, &UMainInteractionWidget::OnSlotSelected);
}

void UMainInteractionWidget::OnSlotSelected(UWeaponSlot* CreatedSlot)
{
	OnWeaponSlotCreated(CreatedSlot);
}
