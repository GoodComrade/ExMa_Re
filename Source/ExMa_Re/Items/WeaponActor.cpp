// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/WeaponActor.h"
#include "AbilitySystemComponent.h"

AWeaponActor::AWeaponActor()
{
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
}
