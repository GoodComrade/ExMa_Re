// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/ExMa_WeaponAttributes.h"

void UExMa_WeaponAttributes::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
    Super::PostGameplayEffectExecute(Data);
}

float UExMa_WeaponAttributes::GetAttribute(EWeaponAttributeType IWeaponAttributeType) const
{
    switch (IWeaponAttributeType)
    {
    case EWeaponAttributeType::Damage:
        return Damage.GetCurrentValue();
    case EWeaponAttributeType::AttackCost:
        return AttackCost.GetCurrentValue();
    case EWeaponAttributeType::Cooldown:
        return Cooldown.GetCurrentValue();
    case EWeaponAttributeType::ShootDelay:
        return ShootDelay.GetCurrentValue();
    case EWeaponAttributeType::ReloadTime:
        return ReloadTime.GetCurrentValue();
    case EWeaponAttributeType::Spread:
        return Spread.GetCurrentValue();
    case EWeaponAttributeType::MaxBulletsCount:
        return MaxBulletsCount.GetCurrentValue();
    case EWeaponAttributeType::CurrentMagazineAmount:
        return CurrentMagazineAmount.GetCurrentValue();
    case EWeaponAttributeType::MagazineSize:
        return MagazineSize.GetCurrentValue();
    //case EWeaponAttributeType::BurstSize:
    //    return BurstSize.GetCurrentValue();
    //case EWeaponAttributeType::BurstDelay:
    //    return BurstDelay.GetCurrentValue();
    case EWeaponAttributeType::MaxRange:
        return MaxRange.GetCurrentValue();
    //case EWeaponAttributeType::MinBulletsInShot:
    //    return MinBulletsInShot.GetCurrentValue();
    //case EWeaponAttributeType::MaxBulletsInShot:
    //    return MaxBulletsInShot.GetCurrentValue();
    case EWeaponAttributeType::Health:
        return Health.GetCurrentValue();
    case EWeaponAttributeType::MaxHealth:
        return MaxHealth.GetCurrentValue();
    //case EWeaponAttributeType::AimType:
    //    return AimType.GetCurrentValue();
    //case EWeaponAttributeType::BlustRadius:
    //    return BlustRadius.GetCurrentValue();
    case EWeaponAttributeType::AimTime:
        return AimTime.GetCurrentValue();
    }

	return 0.0f;
}
