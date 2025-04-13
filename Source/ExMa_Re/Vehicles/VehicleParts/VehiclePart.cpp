// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicles/VehicleParts/VehiclePart.h"
#include "ExMa_Re/DataAssets/Vehicles/VehicleParts/VehiclePartDataAsset.h"

// Sets default values
AVehiclePart::AVehiclePart()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	VehiclePartMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VehiclePartMesh"));
	VehiclePartMesh->SetupAttachment(RootComponent);
	VehiclePartData = nullptr;
}

void AVehiclePart::SetVehiclePartData(UVehiclePartDataAsset* DataToSet)
{
	VehiclePartData = DataToSet;
}

void AVehiclePart::SetVehiclePartMesh(UStaticMesh* MeshToSet)
{
	VehiclePartMesh->SetStaticMesh(MeshToSet);
}

// Called when the game starts or when spawned
void AVehiclePart::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AVehiclePart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

