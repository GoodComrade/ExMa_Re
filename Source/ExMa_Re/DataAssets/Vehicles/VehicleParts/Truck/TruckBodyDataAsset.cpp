// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/Vehicles/VehicleParts/Truck/TruckBodyDataAsset.h"

UTruckBodyDataAsset::UTruckBodyDataAsset(const FObjectInitializer& ObjectInitializer) : UVehiclePartDataAsset(ObjectInitializer)
{
	//TruckBody Properties Init
	TrunkSize = FTileStruct(0, 0);
}
