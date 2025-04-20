// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/Vehicles/VehicleParts/VehiclePartDataAsset.h"
#include "ExMa_Re/Vehicles/VehicleParts/VehiclePart.h"
#include "ExMa_Re/Structs/WeaponSlotInfo.h"


UVehiclePartDataAsset::UVehiclePartDataAsset(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	//VehiclePartClass = AVehiclePart::StaticClass();
	//VehiclePartMesh = nullptr;
}

#if WITH_EDITOR
void UVehiclePartDataAsset::PostInitProperties()
{
    Super::PostInitProperties();
    if (!HasAnyFlags(RF_ClassDefaultObject))
    {
        for (FWeaponSlotInfo& Slot : WeaponSlots)
        {
            Slot.UpdateKey();
        }
    }
}

#endif

void UVehiclePartDataAsset::PostLoad()
{
    Super::PostLoad();
    for (FWeaponSlotInfo& Slot :  WeaponSlots)
    {
        Slot.UpdateKey();
    }
}

