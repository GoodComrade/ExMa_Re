// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "ExMa_Re/Structs/TileStruct.h"
#include "ExMa_Re/Vehicles/VehicleParts/VehiclePart.h"

#include "Engine/StaticMesh.h"

#include "VehiclePartDataAsset.generated.h"

/**
 * 
 */
UCLASS()
class EXMA_RE_API UVehiclePartDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UVehiclePartDataAsset(const FObjectInitializer& ObjectInitializer);

	TSubclassOf<AVehiclePart> GetVehiclePartClass() { return VehiclePartClass; }

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Health = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxHealth = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Armor = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxArmor = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Weight = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Cost = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float BulletResistance = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ExplosionResistance = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float EnergyResistance = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FTileStruct> WeaponSlots;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	//UStaticMesh* VehiclePartMesh;

protected:
	//TODO: implement AVehiclePart class & set their static version here 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AVehiclePart> VehiclePartClass;
};
