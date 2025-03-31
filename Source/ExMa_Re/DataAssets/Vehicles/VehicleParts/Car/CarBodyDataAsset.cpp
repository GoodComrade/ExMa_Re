// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAssets/Vehicles/VehicleParts/Car/CarBodyDataAsset.h"

UCarBodyDataAsset::UCarBodyDataAsset(const FObjectInitializer& ObjectInitializer) : UVehiclePartDataAsset(ObjectInitializer)
{
	//CarBody Properties Init
	TrunkSize = FTileStruct(0, 0);
}
