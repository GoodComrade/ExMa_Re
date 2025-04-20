// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ChestActor.h"
#include "ExMa_Re/Items/ItemObject.h"
#include "ExMa_Re/Vehicles/ExMa_RePawn.h"
#include "ExMa_Re/ConfigStruct/ItemConfigStruct.h"
#include "ExMa_Re/Components/InventoryComponent.h"
#include "ExMa_Re/Structs/TileStruct.h"
#include "ExMa_Re/Game/ExMa_GameState.h"

// Sets default values
AChestActor::AChestActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ActorMesh"));
	ActorMesh->SetupAttachment(RootComponent);

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}

bool AChestActor::TryTransferStoredItems(UInventoryComponent* InventoryToTransfer)
{
	if (InventoryComponent->GetAllItems().Num() <= 0)
		return false;

	UE_LOG(LogTemp, Warning, TEXT("AChestActor:: Items to transfer %i"), InventoryComponent->GetAllItems().Num());

	for (TPair<UItemObject*, FTileStruct> ItemObject : InventoryComponent->GetAllItems())
	{
		if (InventoryToTransfer->TryAddItem(ItemObject.Key) == false)
		{
			UE_LOG(LogTemp, Warning, TEXT("AChestActor:: FailedToTransferItem"));
			return false;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AChestActor:: ItemTransferedSuccess."));
			InventoryComponent->RemoveItem(ItemObject.Key);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("AChestActor:: AllItemsTransfered! Destroy empty crate!"));
	Destroy();

	return true;
}

int32 AChestActor::GetStoredItemsAmount()
{
	return InventoryComponent->GetAllItems().Num();
}

void AChestActor::RecieveItemsWithOverride(UInventoryComponent* InventoryToRecieveFrom)
{
	InventoryComponent->RemoveAllItems();

	UE_LOG(LogTemp, Warning, TEXT("AChestActor:: Items to Recieve %i"), InventoryToRecieveFrom->GetAllItems().Num());

	for (TPair<UItemObject*, FTileStruct> ItemObject : InventoryToRecieveFrom->GetAllItems())
	{
		if (InventoryComponent->TryAddItem(ItemObject.Key) == false)
		{
			UE_LOG(LogTemp, Warning, TEXT("AChestActor:: FailedToRecieveItem"));
		}
		else
		{
			InventoryToRecieveFrom->RemoveItem(ItemObject.Key);
			UE_LOG(LogTemp, Warning, TEXT("AChestActor:: ItemRecieveSuccess."));
		}
	}
}

// Called when the game starts or when spawned
void AChestActor::BeginPlay()
{
	Super::BeginPlay();

	if(StoredItemsNames.Num() > 0)
		PopulateInventory();
}

void AChestActor::PopulateInventory()
{
	for (FName ItemConfigName : StoredItemsNames)
	{
		UItemObject* ItemToAdd = GetGameState()->CreateItem(ItemConfigName, ItemsDataTable, WeaponsDataTable);

		if (ItemToAdd == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("AChestActor:: GameState return nullptr to add"));
			continue;
		}

		if (InventoryComponent->TryAddItem(ItemToAdd))
		{
			UE_LOG(LogTemp, Warning, TEXT("AChestActor:: ItemObject %s add SUCCESS"), *ItemConfigName.ToString());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("AChestActor:: ItemObject %s ADD FAILED"), *ItemConfigName.ToString());
		}

		//UE_LOG(LogTemp, Warning, TEXT("AItemActor:: CreatingItemObject %s"), *ItemConfigName.ToString());
		//
		//FItemConfigStruct ConfigStruct;
		//if (const FItemConfigStruct* ConfigStructRow = ItemsDataTable->FindRow<FItemConfigStruct>(ItemConfigName, ""))
		//	ConfigStruct = *ConfigStructRow;
		//
		//UItemObject* StoredItem = NewObject<UItemObject>(UItemObject::StaticClass());
		//
		//if (StoredItem == nullptr)
		//{
		//	UE_LOG(LogTemp, Warning, TEXT("AItemActor:: StoredItem '%s' ITEM ISN'T CREATED!"), *ItemConfigName.ToString());
		//	return;
		//}
		//
		//StoredItem->SetDimentions(ConfigStruct.SizeX, ConfigStruct.SizeY);
		//StoredItem->SetIcons(ConfigStruct.Icon, ConfigStruct.IconRotated);
		//StoredItem->SetItemType(ConfigStruct.ItemType);
		//
		//if (InventoryComponent->TryAddItem(StoredItem))
		//{
		//	UE_LOG(LogTemp, Warning, TEXT("AItemActor:: ItemObject %s add SUCCESS"), *ItemConfigName.ToString());
		//}
		//else
		//{
		//	UE_LOG(LogTemp, Error, TEXT("AItemActor:: ItemObject %s ADD FAILED"), *ItemConfigName.ToString());
		//}
	}
}

// Called every frame
void AChestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

AExMa_GameState* AChestActor::GetGameState()
{
	UWorld* World = GetWorld();

	if (World == nullptr)
		return nullptr;

	AExMa_GameState* GameState = World->GetGameState<AExMa_GameState>();

	if (GameState == nullptr)
		return nullptr;

	return GameState;
}