// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ExMa_Re/Items/ItemObject.h"
#include "ExMa_Re/Vehicles/ExMa_RePawn.h"
#include "ExMa_Re/ConfigStruct/ItemConfigStruct.h"
#include "ExMa_Re/Components/InventoryComponent.h"
#include "ExMa_Re/Structs/TileStruct.h"

// Sets default values
AItemActor::AItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ActorMesh"));
	ActorMesh->SetupAttachment(RootComponent);

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComponent"));
}

bool AItemActor::TryTransferStoredItems(UInventoryComponent* InventoryToTransfer)
{
	UE_LOG(LogTemp, Warning, TEXT("AItemActor: Items to transfer %i"), InventoryComponent->GetAllItems().Num());

	for (TPair<UItemObject*, FTileStruct> ItemObject : InventoryComponent->GetAllItems())
	{
		if (InventoryToTransfer->TryAddItem(ItemObject.Key) == false)
		{
			UE_LOG(LogTemp, Warning, TEXT("AItemActor: FailedToTransferItem"));
			return false;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("AItemActor: ItemTransferedSuccess."));
			InventoryComponent->RemoveItem(ItemObject.Key);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("AItemActor: AllItemsTransfered! Destroy empty crate!"));
	Destroy();

	return true;
}

// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();
		
	PopulateInventory();
}

void AItemActor::PopulateInventory()
{
	for (FName ItemConfigName : StoredItemsNames)
	{
		UE_LOG(LogTemp, Warning, TEXT("AItemActor: CreatingItemObject %s"), *ItemConfigName.ToString());

		FItemConfigStruct ConfigStruct;
		if (const FItemConfigStruct* ConfigStructRow = ItemsDataTable->FindRow<FItemConfigStruct>(ItemConfigName, ""))
			ConfigStruct = *ConfigStructRow;

		UItemObject* StoredItem = NewObject<UItemObject>(UItemObject::StaticClass());

		if (StoredItem == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("StoredItem '%s' ITEM ISN'T CREATED!"), *ItemConfigName.ToString());
			return;
		}

		StoredItem->SetDimentions(ConfigStruct.SizeX, ConfigStruct.SizeY);
		StoredItem->SetIcons(ConfigStruct.Icon, ConfigStruct.IconRotated);

		if (InventoryComponent->TryAddItem(StoredItem))
		{
			UE_LOG(LogTemp, Warning, TEXT("AItemActor: ItemObject %s add SUCCESS"), *ItemConfigName.ToString());
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("AItemActor: ItemObject %s ADD FAILED"), *ItemConfigName.ToString());
		}
	}
}

// Called every frame
void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

