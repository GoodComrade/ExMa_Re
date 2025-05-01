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

void AVehiclePart::ProcessDeathLogic()
{
	if (!VehiclePartMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("AVehiclePart::ProcessDeathLogic: VehiclePartMesh == nullptr"));
		return;
	}
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	VehiclePartMesh->SetCollisionProfileName(FName("BlockAll"));

	VehiclePartMesh->RecreatePhysicsState();

	VehiclePartMesh->SetEnableGravity(true);
	VehiclePartMesh->SetUseCCD(true);
	VehiclePartMesh->SetSimulatePhysics(true);

	FVector UpwardImpulse(0.0f, 0.0f, 800.0f);
	VehiclePartMesh->AddImpulse(UpwardImpulse, NAME_None, true);

	UE_LOG(LogTemp, Warning, TEXT("AVehiclePart::ProcessDeathLogic: VehiclePartMesh Detached"));

	//SetLifeSpan(10.0f);
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

