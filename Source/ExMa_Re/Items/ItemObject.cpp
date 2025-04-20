// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemObject.h"
#include "ExMa_Re/DataAssets/ItemDataAsset.h"
#include "ExMa_Re/Items/ItemActor.h"

void UItemObject::SetDimentions(int DimentionX, int DimentionY)
{
	Dimensions = FVector2D(DimentionX, DimentionY);
	UE_LOG(LogTemp, Warning, TEXT("UItemObject:: Dimentions set"));
}

void UItemObject::SetIcons(UMaterialInterface* InIcon, UMaterialInterface* InIconRotated)
{
	Icon = InIcon;
	IconRotated = InIconRotated;
	UE_LOG(LogTemp, Warning, TEXT("UItemObject:: Icons Set"));
}

void UItemObject::SetItemActorClass(TSubclassOf<AItemActor> InItemActorClass)
{
	ItemActorClass = InItemActorClass;
}

void UItemObject::SetItemData(UItemDataAsset* DataToSet)
{
	ItemData = DataToSet;
}

void UItemObject::SetItemOwner(AActor* OwnerToSet)
{
	ItemOwner = OwnerToSet;
}

void UItemObject::Rotate()
{
	bIsRotated = !bIsRotated;
}
