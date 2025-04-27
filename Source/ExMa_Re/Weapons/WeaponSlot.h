// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFramework/Actor.h"

#include "ExMa_Re/Structs/TileStruct.h"

#include "ExMa_Re/Items/WeaponItemObject.h"
#include "ExMa_Re/Items/WeaponActor.h"
#include "Templates/Tuple.h"
#include "WeaponSlot.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWeaponSlotChanged);

USTRUCT(BlueprintType)
struct FWeaponSlotStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyTuple")
	UItemObject* WeaponObject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyTuple")
	FTileStruct WeaponObjectDimentions;

	FWeaponSlotStruct()
		: WeaponObject(nullptr), WeaponObjectDimentions(FTileStruct())
	{
	}

	FWeaponSlotStruct(UItemObject* InWeaponObject, FTileStruct InWeaponObjectDimentions)
		: WeaponObject(InWeaponObject), WeaponObjectDimentions(InWeaponObjectDimentions)
	{
	}
};

UCLASS(Blueprintable, BlueprintType, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class EXMA_RE_API UWeaponSlot : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable, Category = "Event Dispatchers")
	FOnWeaponSlotChanged OnWeaponSlotChanged;

	UFUNCTION(BlueprintCallable)
	FWeaponSlotStruct GetWeaponObjectAtSlot() const;

	UFUNCTION(BlueprintCallable)
	void InitWeaponSlot(AActor* OwnerToSet, FTileStruct DimentionsToSet, FName SocketNameToSet);

	UFUNCTION(BlueprintCallable)
	bool TryAddWeapon(UWeaponItemObject* WeaponToSet);

	UFUNCTION(BlueprintCallable)
	void AddWeaponInSlot(UWeaponItemObject* WeaponToSet);

	UFUNCTION(BlueprintCallable)
	void RemoveWeaponFromSlot(UWeaponItemObject* WeaponToRemove);

	UFUNCTION(BlueprintCallable)
	bool IsSlotAvaliable(UWeaponItemObject* InWeapon, FTileStruct SlotSize);

	UFUNCTION(BlueprintCallable)
	bool IsDimentionsMatching(UWeaponItemObject* WeaponToCheck, FTileStruct SlotSize);

	UFUNCTION(BlueprintCallable)
	bool HasWeaponInSlot();

	UFUNCTION(BlueprintCallable)
	void SetFireGroupTag(FGameplayTag InFireGroupTag);

private:
	void SetSlotOwner(AActor* OwnerToSet);

	void SetSlotSocketName(FName SocketName);

	void SetSlotDimensions(FTileStruct DimentionsToSet);

	void InitWeaponActor();

public:
	UFUNCTION(BlueprintCallable, BlueprintPure)
	FTileStruct GetSlotDimensions() const { return SlotDimentions; };

	UFUNCTION(BlueprintCallable, BlueprintPure)
	UWeaponItemObject* GetInstalledWeaponObject() const { return InstalledWeapon; };

	UFUNCTION(BlueprintCallable, BlueprintPure)
	AWeaponActor* GetInstalledWeaponActor() const { return InstalledWeaponActor; };

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FName GetSlotSocketName() const { return SlotSocket; };

	UFUNCTION(BlueprintCallable, BlueprintPure)
	AActor* GetSlotOwner() const { return SlotOwner; };

	UFUNCTION(BlueprintCallable, BlueprintPure)
	FGameplayTag GetFireGroupTag() const { return FireGroupTag; };
private:
	UFUNCTION()
	void SetWeaponActor();

	UFUNCTION()
	void ReturnWeaponObjectToInventory();

private:
	UPROPERTY()
	FTileStruct SlotDimentions;

	UPROPERTY()
	UWeaponItemObject* InstalledWeapon;

	UPROPERTY()
	AWeaponActor* InstalledWeaponActor;

	UPROPERTY()
	FName SlotSocket;

	UPROPERTY()
	AActor* SlotOwner = nullptr;

	UPROPERTY()
	FGameplayTag FireGroupTag;
};
