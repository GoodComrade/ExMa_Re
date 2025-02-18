// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/InventoryComponent.h"
#include "ExMa_Re/UI/ExMa_InventoryWidget.h"
#include "ExMa_Re/Items/ItemObject.h"
#include "ExMa_Re/Structs/TileStruct.h"

// Sets default values for this component's properties
UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

TMap<UItemObject*, FTileStruct> UInventoryComponent::GetAllItems() const
{
	TMap<UItemObject*, FTileStruct> AllItems = TMap<UItemObject*, FTileStruct>();

	for (int CurrentItemObjectIndex = 0; CurrentItemObjectIndex < Items.Num(); CurrentItemObjectIndex++)
	{
		FTileStruct Tile = const_cast<UInventoryComponent*>(this)->IndexToTile(CurrentItemObjectIndex);

		if (Items[CurrentItemObjectIndex]->IsValidLowLevel())
		{
			if (AllItems.Contains(Items[CurrentItemObjectIndex]) == false)
				AllItems.Add(Items[CurrentItemObjectIndex], Tile);
		}
	}

	return AllItems;
}

bool UInventoryComponent::TryAddItem(UItemObject* ItemToAdd)
{
	if (ItemToAdd == nullptr)
		return false;

	for (int Index = 0; Index < Items.Num(); Index++)
	{
		if (IsRoomAvaliable(ItemToAdd, Index))
		{
			AddItemAt(ItemToAdd, Index);
			return true;
		}
	}
	
	//Try fit the rotated ItemObject. Return false if fails to add neither
	ItemToAdd->Rotate();

	for (int Index = 0; Index < Items.Num(); Index++)
	{
		if (IsRoomAvaliable(ItemToAdd, Index))
		{
			AddItemAt(ItemToAdd, Index);
			return true;
		}
	}

	return false;
}

void UInventoryComponent::RemoveItem(UItemObject* ItemToRemove)
{
	if (ItemToRemove->IsValidLowLevel() == false)
		return;

	for (int Index = 0; Index < Items.Num(); Index++)
	{
		if (Items[Index] == ItemToRemove)
		{
			Items[Index] = nullptr;
			
		}
	}
	
	//OnInventoryChanged.Broadcast();
	bIsDirty = true;
}

bool UInventoryComponent::IsRoomAvaliable(UItemObject* ItemToCheck, int TopLeftIndex)
{
	FTileStruct TileByIndex = IndexToTile(TopLeftIndex);
	FTileStruct TileToCheck;

	int XFirstIndex = TileByIndex.X;
	int XLastIndex = TileByIndex.X + ItemToCheck->GetDimentions().X;

	int YFirstIndex = TileByIndex.Y;
	int YLastIndex = TileByIndex.Y + ItemToCheck->GetDimentions().Y;

	for (int XIndex = XFirstIndex; XIndex < XLastIndex; XIndex++)
	{
		for (int YIndex = YFirstIndex; YIndex < YLastIndex; YIndex++)
		{
			TileToCheck.X = XIndex;
			TileToCheck.Y = YIndex;
			
			if (IsTileValid(TileToCheck) == false)
				return false;

			int TileIndex = TileToIndex(TileToCheck);

			if (Items.IsValidIndex(TileIndex) == false)
				return false;

			UItemObject* ItemAtIndex = GetItemAtIndex(TileIndex);

			if (ItemAtIndex != nullptr)
				return false;
		}
	}

	return true;
}

FTileStruct UInventoryComponent::IndexToTile(int Index)
{
	FTileStruct StructToReturn;
	StructToReturn.X = Index % Columns;
	StructToReturn.Y = Index / Columns;

	return StructToReturn;
}

int UInventoryComponent::TileToIndex(FTileStruct TileToConvert)
{
	return TileToConvert.X + TileToConvert.Y * Columns;
}

bool UInventoryComponent::IsTileValid(FTileStruct TileToCheck)
{
	return TileToCheck.X >= 0 && TileToCheck.X < Columns && TileToCheck.Y >= 0 && TileToCheck.Y < Rows;
}

UItemObject* UInventoryComponent::GetItemAtIndex(int Index)
{
	return Items[Index];
}

void UInventoryComponent::AddItemAt(UItemObject* ItemObject, int TopLeftIndex)
{
	FTileStruct TileByIndex = IndexToTile(TopLeftIndex);
	FTileStruct TileToCheck;

	int XFirstIndex = TileByIndex.X;
	int XLastIndex = TileByIndex.X + ItemObject->GetDimentions().X;

	int YFirstIndex = TileByIndex.Y;
	int YLastIndex = TileByIndex.Y + ItemObject->GetDimentions().Y;

	for (int XIndex = XFirstIndex; XIndex < XLastIndex; XIndex++)
	{
		for (int YIndex = YFirstIndex; YIndex < YLastIndex; YIndex++)
		{
			TileToCheck.X = XIndex;
			TileToCheck.Y = YIndex;

			if (IsTileValid(TileToCheck) == false)
				return;

			int TileIndex = TileToIndex(TileToCheck);

			Items[TileIndex] = ItemObject;
		}
	}

	//OnInventoryChanged.Broadcast();
	bIsDirty = true;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	if (Items.Num() > 0)
		Items.Empty();

	Items.SetNum(Columns * Rows);
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsDirty)
	{
		bIsDirty = false;
		OnInventoryChanged.Broadcast();
	}
}

