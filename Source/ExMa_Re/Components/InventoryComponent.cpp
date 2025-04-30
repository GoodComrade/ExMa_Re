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

		if (Items[CurrentItemObjectIndex] != NULL)
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
	{
		UE_LOG(LogTemp, Error, TEXT("UInventoryComponent:: ItemToAdd is nullptr!"));
		return false;
	}

	UE_LOG(LogTemp, Error, TEXT("UInventoryComponent:: Inventory size: %i!"), Items.Num());

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

	UE_LOG(LogTemp, Error, TEXT("UInventoryComponent:: No space to add item!"));
	return false;
}

void UInventoryComponent::RemoveItem(UItemObject* ItemToRemove)
{
	if (ItemToRemove == NULL)
		return;

	for (int Index = 0; Index < Items.Num(); Index++)
	{
		if (Items[Index] == ItemToRemove)
		{
			Items[Index] = nullptr;
			
		}
	}
	
	OnInventoryChanged.Broadcast();
}

void UInventoryComponent::RemoveAllItems()
{
	for (int Index = 0; Index < Items.Num(); Index++)
	{
		Items[Index] = nullptr;
	}

	OnInventoryChanged.Broadcast();
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
			{
				//UE_LOG(LogTemp, Error, TEXT("UInventoryComponent:: Invalid Tile!"));
				return false;
			}

			int TileIndex = TileToIndex(TileToCheck);

			if (Items.IsValidIndex(TileIndex) == false)
			{
				//UE_LOG(LogTemp, Error, TEXT("UInventoryComponent:: Invalid Index!"));
				return false;
			}

			UItemObject* ItemAtIndex = GetItemAtIndex(TileIndex);

			if (ItemAtIndex != nullptr)
			{
				//UE_LOG(LogTemp, Error, TEXT("UInventoryComponent:: Has Item at index!"));
				return false;
			}
		}
	}

	//UE_LOG(LogTemp, Error, TEXT("UInventoryComponent:: has space to add item!"));
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

void UInventoryComponent::SetSize()
{
	if (Items.Num() > 0)
		Items.Empty();

	Items.SetNum(Columns * Rows);

	UE_LOG(LogTemp, Warning, TEXT("UInventoryComponent:: SIZE SET!"));
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

	OnInventoryChanged.Broadcast();
}

bool UInventoryComponent::IsContainsItem(UItemObject* ItemObjectToCheck)
{
	return GetAllItems().Contains(ItemObjectToCheck);
}

void UInventoryComponent::SetInventorySize(int32 NewColumns, int32 NewRows)
{
	Columns = NewColumns;
	Rows = NewRows;
}

// Called when the game starts
void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	SetSize();
}


// Called every frame
void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

