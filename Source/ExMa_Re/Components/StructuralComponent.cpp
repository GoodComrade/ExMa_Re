// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/StructuralComponent.h"
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

void UStructuralComponent::ProcessDetachComponentsOnDeath()
{
	if (ChassisMesh)
	{
		ChassisMesh->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		ChassisMesh->SetSimulatePhysics(true);
		FVector UpwardImpulse(0.0f, 0.0f, 800.0f);
		ChassisMesh->AddImpulse(UpwardImpulse, NAME_None, true);
	}

	if (VehicleCabin)
	{
		VehicleCabin->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		UPrimitiveComponent* CabinRoot = Cast<UPrimitiveComponent>(VehicleCabin->GetRootComponent());
		if (CabinRoot)
		{
			CabinRoot->SetSimulatePhysics(true);
			FVector UpwardImpulse(0.0f, 0.0f, 1000.0f);
			CabinRoot->AddImpulse(UpwardImpulse, NAME_None, true);
		}
	}

	if (VehicleBody)
	{
		VehicleBody->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

		UPrimitiveComponent* BodyRoot = Cast<UPrimitiveComponent>(VehicleBody->GetRootComponent());
		if (BodyRoot)
		{
			BodyRoot->SetSimulatePhysics(true);
			FVector UpwardImpulse(0.0f, 0.0f, 1000.0f);
			BodyRoot->AddImpulse(UpwardImpulse, NAME_None, true);
		}
	}
}

