// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/WeaponGameplayAbility.h"

#include "GameFramework/PlayerState.h"
#include "AbilitySystemBlueprintLibrary.h"

#include "ExMa_Re/Weapons/ExMa_WeaponAttributes.h"
#include "ExMa_Re/Items/WeaponActor.h"
#include "ExMa_Re/Vehicles/ExMa_RePawn.h"

#include "Kismet/KismetMathLibrary.h"
#include "ExMa_Re/ExMaGameplayTags.h"

float UWeaponGameplayAbility::GetWeaponAttribute(EWeaponAttributeType WeaponAttribute) const
{
    if (AbillityWeapon)
    {
        if (const auto WeaponAttributes = AbillityWeapon->GetWeaponAttributes())
        {
            return WeaponAttributes->GetAttribute(WeaponAttribute);
        }

        //return ModifyAttributes(WeaponAttribute, WeaponVal, CharacterVal);
    }

    return 0.f;
}

TArray<FGameplayEffectSpecHandle> UWeaponGameplayAbility::GetGrantedProjectileEffects_Implementation()
{
    TArray<FGameplayEffectSpecHandle> GrantedEffects;

    //TODO: whink about implement damage modifiers
    //if (AbillityWeapon)
    //{
    //    FWeaponConfigStruct WeaponConfig = AbillityWeapon->GetWeaponConfig();
    //
    //    if (AGoodHeroPlayer* OwnerPlayer = Cast< AGoodHeroPlayer>(AbillityWeapon->OwnerCharacter))
    //    {
    //        UAbilityUpgradesComponent* AbilityUpgradesComponent = OwnerPlayer->GetAbilityUpgradesComponent();
    //
    //        if (WeaponConfig.AcidDamage > 0)
    //        {
    //            FAcidEffectParams AcidEffectParams = FAcidEffectParams(AbillityWeapon->GetWeaponConfig());
    //            AbilityUpgradesComponent->UpgradeAcidEffectParams(AcidEffectParams);
    //
    //            AcidEffectSpec.CreateEffects(AcidEffectParams, GrantedEffects, this, GetTargetTagRequirements());
    //        }
    //
    //        if (WeaponConfig.EnergyDamage > 0)
    //        {
    //            FEnergyEffectParams EnergyEffectParams = FEnergyEffectParams(AbillityWeapon->GetWeaponConfig());
    //            AbilityUpgradesComponent->UpgradeEnergyEffectParams(EnergyEffectParams);
    //
    //            EnergyEffectSpec.CreateEffects(EnergyEffectParams, GrantedEffects, this, GetTargetTagRequirements());
    //        }
    //    }
    //}

    return GrantedEffects;
}

/*float UWeaponGameplayAbility::ModifyAttributes(EWeaponAttributeType WeaponAttribute, float WeaponVal, float CharacterVal)
{
    switch(WeaponAttribute)
    {
    case EWeaponAttributeType::Damage:
        return WeaponVal * (1 + CharacterVal / 100);
    case EWeaponAttributeType::AttackCost:
        return WeaponVal; // * (1 - CharacterVal / 100);
    case EWeaponAttributeType::Cooldown:
        return WeaponVal * (1 - CharacterVal / 100);
    case EWeaponAttributeType::ReloadTime:
        return WeaponVal * (1 - CharacterVal / 100);
    case EWeaponAttributeType::Spread:
        return WeaponVal * (1 + CharacterVal / 100);
    case EWeaponAttributeType::MaxBulletsCount:
        return WeaponVal * (1 + CharacterVal / 100);
    //case EWeaponAttributeType::CurrentBulletsCount:
    //    return WeaponVal;
    case EWeaponAttributeType::MagazineSize:
        return WeaponVal * (1 + CharacterVal / 100);
    case EWeaponAttributeType::CurrentMagazineAmount:
        return WeaponVal;
    case EWeaponAttributeType::BurstSize:
        return WeaponVal * (1 + CharacterVal / 100);
    //case EWeaponAttributeType::CurrentBurstSize:
    //    return WeaponVal;
    case EWeaponAttributeType::MinBulletsInShot:
        return WeaponVal + CharacterVal;
    case EWeaponAttributeType::MaxBulletsInShot:
        return WeaponVal + CharacterVal;
    case EWeaponAttributeType::MaxRange:
        return WeaponVal * (1 + CharacterVal / 100);
    //case EWeaponAttributeType::MinRange:
    //    return WeaponVal * (1 + CharacterVal / 100);
    case EWeaponAttributeType::Health:
        return WeaponVal;
    case EWeaponAttributeType::MaxHealth:
        return WeaponVal * (1 + CharacterVal / 100);
    case EWeaponAttributeType::BurstDelay:
        return WeaponVal * (1 - CharacterVal / 100);
    //case EWeaponAttributeType::ProjectileGravityMultiplier:
    //    return WeaponVal * (1 + CharacterVal / 100);
    //case EWeaponAttributeType::AttackMontagePlayRate:
    //    return WeaponVal;
    case EWeaponAttributeType::AimType:
        return WeaponVal;
    default:
        return WeaponVal;
    }
}*/

//TArray<FAreaEffectSpec> UWeaponGameplayAbility::GetAreaEffects()
//{
//    TArray<FAreaEffectSpec> AreaEffects;
//
//    if (AbillityWeapon)
//    {
//        FWeaponConfigStruct WeaponConfig = AbillityWeapon->GetWeaponConfig();
//        if (AGoodHeroPlayer* OwnerPlayer = Cast< AGoodHeroPlayer>(AbillityWeapon->OwnerCharacter))
//        {
//            UAbilityUpgradesComponent* AbilityUpgradesComponent = OwnerPlayer->GetAbilityUpgradesComponent();
//
//            if (WeaponConfig.FireDamage > 0)
//            {
//                FFireAreaEffectParams FireAreaEffectParams = FFireAreaEffectParams(WeaponConfig);
//                AbilityUpgradesComponent->UpgradeFireAreaEffectParams(FireAreaEffectParams);
//
//                AreaEffects.Add(CreateFireAreaEffect(FireAreaEffectParams));
//            }
//
//            if (WeaponConfig.FrozenDamage > 0)
//            {
//                FFrozenAreaEffectParams FrozenAreaEffectParams = FFrozenAreaEffectParams(WeaponConfig);
//                AbilityUpgradesComponent->UpgradeFrozenAreaEffectParams(FrozenAreaEffectParams);
//
//                AreaEffects.Add(CreateFrozenAreaEffect(FrozenAreaEffectParams));
//            }
//
//            if (WeaponConfig.BurnAreaDamage > 0)
//            {
//                FBurnAreaEffectParams BurnAreaEffectParams = FBurnAreaEffectParams(WeaponConfig);
//                AbilityUpgradesComponent->UpgradeFireEffectParams(BurnAreaEffectParams.FireEffectParams);
//
//                AreaEffects.Add(CreateBurnAreaEffect(BurnAreaEffectParams));
//            }
//        }
//    }
//
//    return AreaEffects;
//}

//bool UWeaponGameplayAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags, const FGameplayTagContainer* TargetTags, OUT FGameplayTagContainer* OptionalRelevantTags) const
//{
//    if (Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags))
//        return OwnerCharacterCanActivateAbility();
//
//    return false;
//}
//
//bool UWeaponGameplayAbility::CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags)
//{
//    if (Super::CommitAbility(Handle, ActorInfo, ActivationInfo, OptionalRelevantTags))
//        return OwnerCharacterCanActivateAbility();
//
//    return false;
//}
//
//bool UWeaponGameplayAbility::OwnerCharacterCanActivateAbility() const
//{
//    if (AbillityWeapon)
//    {
//        AExMa_RePawn* OwnerCharacter = Cast<AExMa_RePawn>(AbillityWeapon->GetWeaponOwner());
//
//        if(OwnerCharacter)
//            return CharacterActivateAbilityTagRequirements.RequirementsMet(OwnerCharacter->GetAbilitySystemComponent()->GetOwnedGameplayTags());
//    }
//
//    // If here is no owner character that we should not block ability activation
//    return true;
//}

//FGameplayTagRequirements UWeaponGameplayAbility::GetTargetTagRequirements()
//{
//    return FGameplayTagRequirements();
//}

/*void UWeaponGameplayAbility::AttributeCalculations()
{
    if (!DamageEffectSpecHandle) return;

    DamageEffectSpec = MakeOutgoingGameplayEffectSpec(DamageEffectSpecHandle, 1);
    if (!DamageEffectSpec.IsValid()) return;

    FGameplayEffectSpec* EffectSpec = DamageEffectSpec.Data.Get();
    if (!EffectSpec) return;

    float DamageAttribute = GetModifiedAttribute(EWeaponAttributeType::Damage);
    EffectSpec->SetSetByCallerMagnitude(ExMaGameplayTags::TAG_Ability_Damage, DamageAttribute);

    //BurstSize = FMath::Clamp(FMath::TruncToInt32(GetModifiedAttribute(EWeaponAttributeType::MaxBurstSize)), 0, GetModifiedAttribute(EWeaponAttribute::CurrentMagazineSize));
}*/
