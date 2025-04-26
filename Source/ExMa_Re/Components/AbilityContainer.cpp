// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AbilityContainer.h"

#include "GameplayTagContainer.h"
#include "AbilitySystemComponent.h"

#include "ExMa_Re/Items/WeaponActor.h"
#include "ExMa_Re/Vehicles/ExMa_RePawn.h"

// Sets default values for this component's properties
UAbilityContainer::UAbilityContainer()
{
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UAbilityContainer::BeginPlay()
{
	Super::BeginPlay();
}

bool UAbilityContainer::CastPrimaryAttack()
{
    if (bCanCastAbilities)
    {
        return AbilitySystem->TryActivateAbility(PrimaryAttackHandle);
    }
    return false;
}

void UAbilityContainer::CastReload()
{
    if (bCanCastAbilities)
    {
        AbilitySystem->TryActivateAbility(ReloadHandle);
    }
}

void UAbilityContainer::InitComponent()
{
    const AWeaponActor* Weapon = Cast<AWeaponActor>(GetOwner());
    check(Weapon);

    AbilitySystem = Weapon->GetAbilitySystemComponent();

    
}

void UAbilityContainer::SetAbilities(TSubclassOf<class UGameplayAbility> InPrimaryAttack, 
                                     TSubclassOf<class UGameplayAbility> InReload)
{
    PrimaryAttack = InPrimaryAttack;
    Reload = InReload;

    InitAbilities();
}

void UAbilityContainer::InitAbilities()
{
    if (IsValid(PrimaryAttack))
    {
        //UGameplayAbility *Ability = PrimaryAttack->GetDefaultObject<UGameplayAbility>();
        const FGameplayAbilitySpec AbilitySpec(PrimaryAttack);
        PrimaryAttackHandle = AbilitySystem->GiveAbility(AbilitySpec);
    }
    if (IsValid(Reload))
    {
        const FGameplayAbilitySpec AbilitySpec(Reload);
        ReloadHandle = AbilitySystem->GiveAbility(AbilitySpec);
    }
}
