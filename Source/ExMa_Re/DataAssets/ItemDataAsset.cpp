// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/ItemDataAsset.h"

#include "ExMa_Re/Items/ItemObject.h"

UItemObject* UItemDataAsset::ConstructItemInstance(UItemDataAsset* ItemData)
{
	return ItemData->ConstructItemInstance();
}

UItemDataAsset::UItemDataAsset(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	ItemObjectClass = UItemObject::StaticClass();
}

UItemObject* UItemDataAsset::ConstructItemInstance()
{
	UItemObject* ItemObject = NewObject<UItemObject>(this, ItemObjectClass);
	ItemObject->SetItemData(this);

	return ItemObject;
}
