// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StructuralComponent.h"
#include "Engine/Texture2D.h"
#include "ExMa_Re/Vehicles/VehicleParts/DestroyedPart.h"
#include "Engine/StaticMeshSocket.h"

// Sets default values for this component's properties
UStructuralComponent::UStructuralComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	VehicleCabin = nullptr;
	VehicleBody = nullptr;
}


// Called when the game starts
void UStructuralComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

// Called every frame
void UStructuralComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

AVehiclePart* UStructuralComponent::GetTargetVehiclePartBySocket(FName SocketName)
{
	if (VehicleCabin)
	{
		UStaticMesh* Mesh = VehicleCabin->GetVehicleStaticMeshComponent()->GetStaticMesh();
		if (!Mesh)
		{
			UE_LOG(LogTemp, Warning, TEXT("UStructuralComponent::GetTargetVehiclePartBySocket: Mesh == nullptr"));
			return nullptr;
		}

		for (const UStaticMeshSocket* Socket : Mesh->Sockets)
		{
			if (Socket)
			{
				UE_LOG(LogTemp, Warning, TEXT("UStructuralComponent::GetTargetVehiclePartBySocket: TargetSocket: %s, LookAtSocket: %s"), *SocketName.ToString(), *Socket->SocketName.ToString());
				if (SocketName == Socket->SocketName)
					return VehicleCabin;
			}
				
		}
	}

	if (VehicleBody)
	{
		UStaticMesh* Mesh = VehicleBody->GetVehicleStaticMeshComponent()->GetStaticMesh();
		if (!Mesh)
		{
			UE_LOG(LogTemp, Warning, TEXT("UStructuralComponent::GetTargetVehiclePartBySocket: Mesh == nullptr"));
			return nullptr;
		}

		// Итерируемся по массиву сокетов в статической сетке
		for (const UStaticMeshSocket* Socket : Mesh->Sockets)
		{
			if (Socket)
			{
				UE_LOG(LogTemp, Warning, TEXT("UStructuralComponent::GetTargetVehiclePartBySocket: TargetSocket: %s, LookAtSocket: %s"), *SocketName.ToString(), *Socket->SocketName.ToString());
				if (SocketName == Socket->SocketName)
					return VehicleBody;
			}
				
		}
	}

	return nullptr;
}

void UStructuralComponent::SetVehicleCabin(AVehiclePart* CabinToSet)
{
	DestroyCabin();

	VehicleCabin = CabinToSet;
	VehicleCabin->AttachToComponent(ChassisMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("CabinSocket"));
	VehicleCabin->SetRootComponent(ChassisMesh);
}

void UStructuralComponent::SetVehicleBody(AVehiclePart* BodyToSet)
{
	DestroyBody();

	VehicleBody = BodyToSet;
	VehicleBody->AttachToComponent(ChassisMesh, FAttachmentTransformRules::SnapToTargetNotIncludingScale, FName("BodySocket"));
	VehicleBody->SetRootComponent(ChassisMesh);
}

void UStructuralComponent::DestroyCabin()
{
	if (VehicleCabin != nullptr)
		VehicleCabin->Destroy();
}

void UStructuralComponent::DestroyBody()
{
	if (VehicleBody != nullptr)
		VehicleBody->Destroy();
}

void UStructuralComponent::ProcessDetachComponentsOnDeath(UTexture2D* InDeathTexture)
{
	if (ChassisMesh)
	{
		FTransform TireFrontLeftWorldTransform = ChassisMesh->GetComponentTransform();

		ADestroyedPart* TireFrontLeftDestroyed = GetWorld()->SpawnActor<ADestroyedPart>(ADestroyedPart::StaticClass(), TireFrontLeftWorldTransform);
		if (TireFrontLeftDestroyed)
			TireFrontLeftDestroyed->Init(ChassisMesh->GetStaticMesh(), GetOwner()->GetActorLocation(), InDeathTexture);

		//int32 MaterialCount = ChassisMesh->GetNumMaterials();
		//
		//for (int32 Index = 0; Index < MaterialCount; ++Index)
		//{
		//	UMaterialInterface* BaseMaterial = ChassisMesh->GetMaterial(Index);
		//	if (!BaseMaterial) continue;
		//
		//	UMaterialInstanceDynamic* DynMaterial = ChassisMesh->CreateAndSetMaterialInstanceDynamicFromMaterial(Index, BaseMaterial);
		//	if (!DynMaterial) continue;
		//
		//	DynMaterial->SetTextureParameterValue("TargetColor", InDeathTexture);
		//}
		//
		//ChassisMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		//ChassisMesh->SetCollisionProfileName(FName("BlockAll"));
		//
		//ChassisMesh->RecreatePhysicsState();
		//
		//ChassisMesh->SetEnableGravity(true);
		//ChassisMesh->SetSimulatePhysics(true);
		//ChassisMesh->SetUseCCD(true);
		//
		//FVector UpwardImpulse(0.0f, 0.0f, 400.0f);
		//ChassisMesh->AddImpulse(UpwardImpulse, NAME_None, true);

		UE_LOG(LogTemp, Warning, TEXT("UStructuralComponent::ProcessDetachComponentsOnDeath: ChassisMesh detached!"));
	}

	if (VehicleCabin)
	{
		VehicleCabin->ProcessDeathLogic(InDeathTexture);

		UE_LOG(LogTemp, Warning, TEXT("UStructuralComponent::ProcessDetachComponentsOnDeath: VehicleCabin detached!"));
	}

	if (VehicleBody)
	{
		VehicleBody->ProcessDeathLogic(InDeathTexture);

		UE_LOG(LogTemp, Warning, TEXT("UStructuralComponent::ProcessDetachComponentsOnDeath: VehicleBody detached!"));
	}
}

