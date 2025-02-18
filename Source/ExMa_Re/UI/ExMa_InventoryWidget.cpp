// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ExMa_InventoryWidget.h"
#include "ExMa_Re/Components/InventoryComponent.h"

void UExMa_InventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UExMa_InventoryWidget::SetComponents(APlayerController* InPlayerController, UInventoryComponent* InInventoryComponentRef)
{
	if (InPlayerController == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UExMa_InventoryWidget: InPlayerComponent IS NULL"));
		return;
	}

	PlayerController = InPlayerController;

	if (InInventoryComponentRef == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UExMa_InventoryWidget: InventoryComponentRef IS NULL"));
		return;
	}

	InventoryComponentRef = InInventoryComponentRef;
	TileSize = InventoryComponentRef->TileSize;
}


