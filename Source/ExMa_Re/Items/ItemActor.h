// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ExMa_Re/ConfigStruct/ItemConfigStruct.h"
#include "ItemActor.generated.h"

class UItemObject;
class UInventoryComponent;

UCLASS(Blueprintable, BlueprintType)
class EXMA_RE_API AItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemActor();

	UFUNCTION()
	UInventoryComponent* GetInventoryComponentRef() const { return InventoryComponent; };

	UFUNCTION()
	bool TryTransferStoredItems(UInventoryComponent* InventoryToTransfer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void PopulateInventory();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ActorMesh;

	//TODO: Implement more proper way to set this array
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true", InstanceEditable = "true"))
	TArray<FName> StoredItemsNames;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true", InstanceEditable = "true"))
	UDataTable* ItemsDataTable;

	/** Character inventory component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	UInventoryComponent* InventoryComponent;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
