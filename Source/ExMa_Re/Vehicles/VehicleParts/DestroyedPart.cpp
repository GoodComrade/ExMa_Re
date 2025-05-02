// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicles/VehicleParts/DestroyedPart.h"
#include "Engine/Texture2D.h"

// Sets default values
ADestroyedPart::ADestroyedPart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	DestroyedPartMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VehiclePartMesh"));
	DestroyedPartMesh->SetupAttachment(RootComponent);
}

void ADestroyedPart::Init(UStaticMesh* MeshToSet, FVector ImpulseOrigin, UTexture2D* InDeathTexture)
{
	if (!MeshToSet)
	{
		UE_LOG(LogTemp, Warning, TEXT("ADestroyedPart::Init: MeshToSet == nullptr"));
		return;
	}

	DestroyedPartMesh->SetStaticMesh(MeshToSet);

	int32 MaterialCount = DestroyedPartMesh->GetNumMaterials();

	for (int32 Index = 0; Index < MaterialCount; ++Index)
	{
		UMaterialInterface* BaseMaterial = DestroyedPartMesh->GetMaterial(Index);
		if (!BaseMaterial) continue;

		UMaterialInstanceDynamic* DynMaterial = DestroyedPartMesh->CreateAndSetMaterialInstanceDynamicFromMaterial(Index, BaseMaterial);
		if (!DynMaterial) continue;

		DynMaterial->SetTextureParameterValue("TargetColor", InDeathTexture);
	}

	DestroyedPartMesh->SetCollisionProfileName(FName("BlockAll"));

	DestroyedPartMesh->RecreatePhysicsState();

	DestroyedPartMesh->SetEnableGravity(true);
	DestroyedPartMesh->SetUseCCD(true);
	DestroyedPartMesh->SetSimulatePhysics(true);

	FVector TireFrontLeftImpulseDirection = (DestroyedPartMesh->GetComponentLocation() - ImpulseOrigin).GetSafeNormal();
	DestroyedPartMesh->AddImpulse(TireFrontLeftImpulseDirection * 500.0f, NAME_None, true);
}

// Called when the game starts or when spawned
void ADestroyedPart::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestroyedPart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

