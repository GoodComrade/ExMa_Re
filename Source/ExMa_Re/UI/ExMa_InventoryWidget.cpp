// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ExMa_InventoryWidget.h"
#include "ExMa_Re/Components/InventoryComponent.h"

void UExMa_InventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UExMa_InventoryWidget::SetPlayerController(APlayerController* InPlayerController)
{
	PlayerController = InPlayerController;
}

void UExMa_InventoryWidget::SetInventoryComponentRef(UInventoryComponent* InInventoryComponentRef)
{
	if (InInventoryComponentRef == nullptr)
		return;
	
	InventoryComponentRef = InInventoryComponentRef;
	
	if (InventoryComponentRef == nullptr)
		return;
	
	TileSize = InventoryComponentRef->TileSize;
}


