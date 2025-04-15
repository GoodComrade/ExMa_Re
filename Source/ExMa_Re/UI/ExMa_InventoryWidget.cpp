// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ExMa_InventoryWidget.h"
#include "ExMa_Re/Components/InventoryComponent.h"

#include "ExMa_Re/Game/ExMa_GameInstance.h"

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

	UExMa_GameInstance* GameInstance = Cast<UExMa_GameInstance>(GetGameInstance());

	if (GameInstance == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("UExMa_InventoryWidget:: GameInstance is NULLPTR!"));
		return;
	}

	InventoryComponentRef = InInventoryComponentRef;
	TileSize = GameInstance->TileSize;
}


