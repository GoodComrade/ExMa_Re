// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/WeaponActor.h"
#include "AbilitySystemComponent.h"
#include "Animation/AnimBlueprint.h"

AWeaponActor::AWeaponActor()
{
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
	Mesh->BodyInstance.bSimulatePhysics = false;
	Mesh->BodyInstance.bNotifyRigidBodyCollision = false;
	Mesh->BodyInstance.bUseCCD = false;
	Mesh->SetGenerateOverlapEvents(false);
	Mesh->SetCanEverAffectNavigation(false);
	RootComponent = Mesh;

	AbilitySystem = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AblitySystem"));

	Attributes = CreateDefaultSubobject<UExMa_WeaponAttributes>(TEXT("WeaponAttributes"));
	AbilitySystem->AddSpawnedAttribute(Attributes);
}

void AWeaponActor::Tick(float Delta)
{
	Super::Tick(Delta);
}

//void AWeaponActor::SetWeaponAttributes(FWeaponConfigStruct WeaponConfig)
//{
//}

void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();

	if (!WeaponData)
	{
		UE_LOG(LogTemp, Error, TEXT("AWeaponActor::BeginPlay: WeaponData IS NULLPTR!"));
		return;
	}
}

void AWeaponActor::SetWeaponOwner(AActor* OwnerToSet)
{
	if (!OwnerToSet)
	{
		UE_LOG(LogTemp, Error, TEXT("AWeaponActor::SetOwnerPawn: OwnerToSet IS NULLPTR!"));
		return;
	}

	WeaponOwner = OwnerToSet;
}

void AWeaponActor::SetMesh(USkeletalMesh* MeshToSet)
{
	if (!MeshToSet)
	{
		UE_LOG(LogTemp, Error, TEXT("AWeaponActor::SetMesh: MeshToSet IS NULLPTR!"));
		return;
	}

	Mesh->SetSkeletalMesh(MeshToSet);
}

void AWeaponActor::RemoveWeaponOwner()
{
	if (WeaponOwner)
	{
		WeaponOwner = nullptr;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AWeaponActor::RemoveWeaponOwner: WeaponOwner IS NULLPTR!"));
	}
}

void AWeaponActor::RemoveMesh()
{
	if (Mesh)
	{
		Mesh->SetSkeletalMesh(nullptr);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AWeaponActor::RemoveMesh: Mesh IS NULLPTR!"));
	}
}

void AWeaponActor::RemovetMeshAnimInstance()
{
	if (Mesh)
	{
		Mesh->SetAnimInstanceClass(nullptr);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AWeaponActor::RemovetMeshAnimInstance: Mesh IS NULLPTR!"));
	}
}

void AWeaponActor::RemoveWeaponData()
{
	if (WeaponData)
	{
		WeaponData = nullptr;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("AWeaponActor::RemoveWeaponData: WeaponData IS NULLPTR!"));
	}
}

void AWeaponActor::SetMeshAnimInstance(UAnimBlueprint* AnimToSet)
{
	if (!AnimToSet)
	{
		UE_LOG(LogTemp, Error, TEXT("AWeaponActor::SetMeshAnimInstance: AnimToSet IS NULLPTR!"));
		return;
	}
	Mesh->SetAnimInstanceClass(AnimToSet->GeneratedClass);
}

void AWeaponActor::SetWeaponData(UWeaponDataAsset* DataToSet)
{
	if (!DataToSet)
	{
		UE_LOG(LogTemp, Error, TEXT("AWeaponActor::SetWeaponData: DataToSet IS NULLPTR!"));
		return;
	}

	WeaponData = DataToSet;
}
