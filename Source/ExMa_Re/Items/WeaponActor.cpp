// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/WeaponActor.h"
#include "AbilitySystemComponent.h"
#include "ExMa_Re/Components/AbilityContainer.h"
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

	AbilityContainer = CreateDefaultSubobject<UAbilityContainer>(TEXT("AbilityContainer"));
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

	//if (!WeaponData)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("AWeaponActor::BeginPlay: WeaponData IS NULLPTR!"));
	//	return;
	//}

	AbilityContainer->InitComponent();
}

#pragma region WeaponActor

void AWeaponActor::SetWeaponData(UWeaponDataAsset* DataToSet)
{
	if (!DataToSet)
	{
		UE_LOG(LogTemp, Error, TEXT("AWeaponActor::SetWeaponData: DataToSet IS NULLPTR!"));
		return;
	}

	WeaponData = DataToSet;
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

void AWeaponActor::SetWeaponParamsFromData()
{
	SetMesh();
	SetMeshAnimInstance();
	SetWeaponAbilities();
	SetAttributes();
}

#pragma endregion PublicPropertySetters

#pragma region WeaponActor

void AWeaponActor::SetMesh()
{
	if (!WeaponData)
	{
		UE_LOG(LogTemp, Error, TEXT("AWeaponActor::SetMesh: WeaponData IS NULLPTR!"));
		return;
	}

	Mesh->SetSkeletalMesh(WeaponData->WeaponMesh);
}

void AWeaponActor::SetMeshAnimInstance()
{
	if (!WeaponData)
	{
		UE_LOG(LogTemp, Error, TEXT("AWeaponActor::SetMeshAnimInstance: WeaponData IS NULLPTR!"));
		return;
	}
	Mesh->SetAnimInstanceClass(WeaponData->MeshABP->GeneratedClass);
}

void AWeaponActor::SetWeaponAbilities()
{
	if (!WeaponData)
		return;

	AbilityContainer->SetAbilities(WeaponData->FireAbility, WeaponData->ReloadAbility);
}

void AWeaponActor::SetAttributes()
{
	if (!WeaponData)
		return;

	Attributes->SetDamage(WeaponData->Damage);
	Attributes->SetAttackCost(WeaponData->AttackCost);
	Attributes->SetCooldown(WeaponData->Cooldown);
	Attributes->SetShootDelay(WeaponData->ShootDelay);
	Attributes->SetReloadTime(WeaponData->ReloadTime);
	Attributes->SetSpread(WeaponData->Spread);
	Attributes->SetMaxBulletsCount(WeaponData->MaxBulletsCount);
	Attributes->SetCurrentMagazineAmount(WeaponData->CurrenMagazineCapacity);
	Attributes->SetMagazineSize(WeaponData->MaxMagazineCapacity);

	Attributes->SetMinRange(WeaponData->MinRange);
	Attributes->SetMaxRange(WeaponData->MaxRange);


	Attributes->SetHealth(WeaponData->Health);
	Attributes->SetMaxHealth(WeaponData->MaxHealth);





	Attributes->SetAimTime(WeaponData->AimTime);

	UE_LOG(LogTemp, Error, TEXT("AWeaponActor::SetAttributes: AimTime: %.f"), Attributes->GetAimTime());
}

void AWeaponActor::SetAnimMotages()
{
	if (!WeaponData)
		return;

	FireMontage = WeaponData->FireMontage;
	ReloadMontage = WeaponData->ReloadMontage;
}

#pragma endregion PrivatePropertySetters

#pragma region WeaponActor

void AWeaponActor::RemoveWeaponParams()
{
	RemoveWeaponData();
	RemoveWeaponOwner();
	RemoveMesh();
	RemovetMeshAnimInstance();
	RemoveAttributes();
}

#pragma endregion PublicPropertyRemovers

#pragma region WeaponActor

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

void AWeaponActor::RemoveAttributes()
{
	Attributes->SetDamage(0);
	Attributes->SetAttackCost(0);
	Attributes->SetCooldown(0);
	Attributes->SetShootDelay(0);
	Attributes->SetReloadTime(0);
	Attributes->SetSpread(0);
	Attributes->SetMaxBulletsCount(0);
	Attributes->SetCurrentMagazineAmount(0);
	Attributes->SetMagazineSize(0);

	Attributes->SetMinRange(0);
	Attributes->SetMaxRange(0);


	Attributes->SetHealth(0);
	Attributes->SetMaxHealth(0);





	Attributes->SetAimTime(0);
}

#pragma endregion PrivatePropertyRemovers

bool AWeaponActor::CastAttack()
{
	return AbilityContainer->CastPrimaryAttack();
}

void AWeaponActor::CastReload() const
{
	AbilityContainer->CastReload();
}

void AWeaponActor::DisableAbilities()
{
	AbilityContainer->bCanCastAbilities = false;
}

void AWeaponActor::EnableAbilities()
{
	AbilityContainer->bCanCastAbilities = true;
}
