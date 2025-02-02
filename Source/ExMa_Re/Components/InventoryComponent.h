// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ExMa_Re/Structs/TileStruct.h"
#include "Containers/Map.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnInventoryChanged);

class UItemObject;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXMA_RE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

	//TODO: Set two variables below from attributes
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants", meta = (ExposeOnSpawn = "true", InstanceEditable = "true"))
	int32 Columns;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants", meta = (ExposeOnSpawn = "true", InstanceEditable = "true"))
	int32 Rows;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants", meta = (ExposeOnSpawn = "true", InstanceEditable = "true"))
	float TileSize;

	UPROPERTY(BlueprintAssignable, Category = "Event Dispatchers")
	FOnInventoryChanged OnInventoryChanged;

	UFUNCTION(BlueprintCallable)
	TMap<UItemObject*, FTileStruct> GetAllItems() const;
	//TODO: rework this logic to adding multiple items
	UFUNCTION(BlueprintCallable)
	bool TryAddItem(UItemObject* ItemToAdd);
	
	UFUNCTION(BlueprintCallable)
	void RemoveItem(UItemObject* ItemToRemove);

	UFUNCTION()
	bool IsRoomAvaliable(UItemObject* ItemToCheck, int TopLeftIndex);
	
	UFUNCTION()
	FTileStruct IndexToTile(int Index);

	UFUNCTION()
	int TileToIndex(FTileStruct TileToConvert) const;

	bool IsTileValid(FTileStruct TileToCheck);

private:

	UPROPERTY()
	TArray<UItemObject*> Items;

	UFUNCTION()
	UItemObject* GetItemAtIndex(int Index);

	UFUNCTION()
	void AddItemAt(UItemObject* ItemObject, int TopLeftIndex);

	UPROPERTY()
	bool IsDirty;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
