// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

#include "ExMa_Re/Structs/TileStruct.h"

#include "ExMa_Re/Items/WeaponItemObject.h"

#include "WeaponSlot.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponSlotChanged);

UCLASS()
class EXMA_RE_API UWeaponSlot : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable, Category = "Event Dispatchers")
	FOnWeaponSlotChanged OnWeaponSlotChanged;

	UFUNCTION(BlueprintCallable)
	void SetSlotDimensions(FTileStruct DimentionsToSet);

	UFUNCTION(BlueprintCallable)
	bool TryAddWeapon(UWeaponItemObject* WeaponToSet);

	UFUNCTION(BlueprintCallable)
	void AddWeaponInSlot(UWeaponItemObject* WeaponToSet);

	UFUNCTION(BlueprintCallable)
	void RemoveWeaponFromSlot(UWeaponItemObject* WeaponToRemove);

	UFUNCTION(BlueprintCallable)
	bool IsDimentionsMatching(UWeaponItemObject* WeaponToCheck, FTileStruct SlotSize);

	UFUNCTION(BlueprintCallable)
	bool HasWeaponInSlot();

public:
	UFUNCTION(BlueprintCallable)
	FTileStruct GetSlotDimensions() { return SlotDimentions; };

private:
	UPROPERTY()
	FTileStruct SlotDimentions;

	UPROPERTY()
	UWeaponItemObject* InstalledWeapon;
};
