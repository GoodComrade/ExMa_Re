// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/Vehicles/VehicleParts/VehiclePartDataAsset.h"
#include "ExMa_Re/Vehicles/VehicleParts/VehiclePart.h"

UVehiclePartDataAsset::UVehiclePartDataAsset(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	VehiclePartClass = AVehiclePart::StaticClass();
	VehiclePartMesh = nullptr;
}
