// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicles/VehicleParts/VehiclePart.h"
#include "ExMa_Re/DataAssets/Vehicles/VehicleParts/VehiclePartDataAsset.h"

// Sets default values
AVehiclePart::AVehiclePart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	VehiclePartMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VehiclePartMesh"));
}

void AVehiclePart::SetVehiclePartData(UVehiclePartDataAsset* DataToSet)
{
	VehiclePartData = DataToSet;
}

void AVehiclePart::SetVehiclePartMesh(UStaticMesh* MeshToSet)
{
	VehiclePartMesh->SetStaticMesh(MeshToSet);
}

void AVehiclePart::ProcessDestroyVehiclePart()
{
	VehiclePartMesh->DestroyComponent();
	Destroy();
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

