// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ExMa_Re/Enums/ItemType.h"
#include "ExMa_Re/Items/ItemInfoStruct.h"
#include "Materials/MaterialInterface.h"
#include "ItemObject.generated.h"

class AItemActor;
class UItemDataAsset;

UCLASS(Blueprintable, BlueprintType)
class EXMA_RE_API UItemObject : public UObject
{
	GENERATED_BODY()

#pragma region ItemObject
public:

	UFUNCTION(BlueprintCallable)
	FVector2D GetDimentions() const { return bIsRotated ? FVector2D(Dimensions.Y, Dimensions.X) : Dimensions; };

	UFUNCTION(BlueprintCallable)
	UMaterialInterface* GetIcon() const { return bIsRotated ? IconRotated : Icon; }

	UFUNCTION(BlueprintCallable)
	TSubclassOf<class AItemActor> GetItemActorClass() const { return ItemActorClass; };

	UFUNCTION(BlueprintCallable)
	UItemDataAsset* GetItemData() const { return ItemData; };

	UFUNCTION(BlueprintCallable)
	FItemInfoStruct GetItemInfo() const { return ItemInfo; };
#pragma endregion Getters

#pragma region ItemObject
public:
	UFUNCTION(BlueprintCallable)
	void SetDimentions(int DimentionX, int DimentionY);

	UFUNCTION(BlueprintCallable)
	void SetIcons(UMaterialInterface* InIcon, UMaterialInterface* InIconRotated);

	//TODO: Remove this because all ItemObjects are will contain as multiple objects in chest item actors.
	//Then we will not need to set scene actor to spawn fro each item object.
	UFUNCTION(BlueprintCallable)
	void SetItemActorClass(TSubclassOf<AItemActor> InItemActorClass);

	UFUNCTION(BlueprintCallable)
	void SetItemData(UItemDataAsset* DataToSet);

	virtual void SetItemInfo();
#pragma endregion Setters

public:
	UFUNCTION(BlueprintCallable)
	void Rotate();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsRotated() const { return bIsRotated; };

#pragma region ItemObject
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true", InstanceEditable = "true"))
	FVector2D Dimensions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true", InstanceEditable = "true"))
	UMaterialInterface* Icon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true", InstanceEditable = "true"))
	UMaterialInterface* IconRotated;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true", InstanceEditable = "true"))
	TSubclassOf<class AItemActor> ItemActorClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn))
	UItemDataAsset* ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true", InstanceEditable = "true"))
	FItemInfoStruct ItemInfo;

	UPROPERTY()
	bool bIsRotated;

#pragma endregion Properties
};
