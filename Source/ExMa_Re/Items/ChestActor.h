// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/ItemActor.h"
#include "Components/StaticMeshComponent.h"
#include "ChestActor.generated.h"

/**
 * 
 */
UCLASS()
class EXMA_RE_API AChestActor : public AItemActor
{
	GENERATED_BODY()

public:
	AChestActor();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	UInventoryComponent* GetInventoryComponentRef() const { return InventoryComponent; };

	UFUNCTION()
	bool TryTransferStoredItems(UInventoryComponent* InventoryToTransfer);

	UFUNCTION()
	int32 GetStoredItemsAmount();

	UFUNCTION()
	void RecieveItemsWithOverride(UInventoryComponent* InventoryToRecieveFrom);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void PopulateInventory();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ActorMesh;

	//TODO: Implement more proper way to set this array
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true", InstanceEditable = "true"))
	TArray<FName> StoredItemsNames;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true", InstanceEditable = "true"))
	UDataTable* ItemsDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true", InstanceEditable = "true"))
	UDataTable* WeaponsDataTable;

	/** Character inventory component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	UInventoryComponent* InventoryComponent;
	
private:
	AExMa_GameState* GetGameState();
};
