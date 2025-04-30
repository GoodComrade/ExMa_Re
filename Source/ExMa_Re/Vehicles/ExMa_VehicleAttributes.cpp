// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicles/ExMa_VehicleAttributes.h"

#include "GameplayEffectExtension.h"
#include "ExMa_Re/Vehicles/ExMa_RePawn.h"
#include "ExMa_Re/Items/WeaponActor.h"

void UExMa_VehicleAttributes::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

    AActor* TargetActor = nullptr;
    AExMa_RePawn* TargetCharacter = nullptr;
    AExMa_RePawn* InstigatorCharacter = nullptr;

    if (AActor* Instigator = Data.EffectSpec.GetEffectContext().GetInstigator())
    {
        InstigatorCharacter = Cast<AExMa_RePawn>(Instigator);
        if (!InstigatorCharacter)
        {
            if (AWeaponActor* WeaponInstigator = Cast<AWeaponActor>(Instigator))
            {
                InstigatorCharacter = Cast<AExMa_RePawn>(WeaponInstigator->GetWeaponOwner());
            }
        }
    }

    if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
    {
        TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
        TargetCharacter = Cast<AExMa_RePawn>(TargetActor);
    }

    if (Data.EvaluatedData.Attribute == GetHealthAttribute())
    {
        SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
    }

    //if (Data.EvaluatedData.Attribute == GetHealPercentageAttribute())
    //{
    //    SetHealth(FMath::Clamp(GetHealth() + GetMaxHealth() * GetHealPercentage(), 0.f, GetMaxHealth()));
    //}

    if (Data.EvaluatedData.Attribute == GetIncomeDamageAttribute())
    {

        if (TargetCharacter)
        {
            //TargetCharacter->LastDamageDealer = InstigatorCharacter;
            if (!TargetCharacter->IsDead())
            {
                float TragerArmor = TargetCharacter->GetAttributes()->GetArmor();

                if (TragerArmor > 0)
                {
                    float DamageAfterShield = GetIncomeDamage() - TragerArmor;

                    if (DamageAfterShield > 0)
                    {
                        // Convert into -Health and then clamp
                        SetHealth(FMath::Clamp(GetHealth() - DamageAfterShield, 0.f, GetMaxHealth()));
                        //TargetCharacter->ApplyDamage(InstigatorCharacter);
                        TargetCharacter->ApplyDamage();
                    }
                }
                else
                {
                    SetHealth(FMath::Clamp(GetHealth() - GetIncomeDamage(), 0.f, GetMaxHealth()));
                    //TargetCharacter->ApplyDamage(InstigatorCharacter);
                    TargetCharacter->ApplyDamage();
                }

            }

            if (TObjectPtr<const UGameplayEffect> Effect = Data.EffectSpec.Def)
            {
                UE_LOG(LogTemp, Display, TEXT("Apply damage from %s to %s by effect: %s"), *InstigatorCharacter->GetName(), *TargetCharacter->GetName(), *Effect.GetName());
            }

            SetIncomeDamage(0.0f);
        }
    }
}

float UExMa_VehicleAttributes::GetAttribute(EVehicleAttributeType IVehicleAttributeType) const
{
    switch (IVehicleAttributeType)
    {
    case EVehicleAttributeType::Health:
        return Health.GetCurrentValue();
    case EVehicleAttributeType::MaxHealth:
        return MaxHealth.GetCurrentValue();
    case EVehicleAttributeType::Armor:
        return Armor.GetCurrentValue();
    case EVehicleAttributeType::MaxArmor:
        return MaxArmor.GetCurrentValue();
    case EVehicleAttributeType::GasTankSize:
        return GasTankSize.GetCurrentValue();
    case EVehicleAttributeType::MaxTorque:
        return MaxTorque.GetCurrentValue();
    case EVehicleAttributeType::MaxRPM:
        return MaxRPM.GetCurrentValue();
    case EVehicleAttributeType::EngineIdleRPM:
        return EngineIdleRPM.GetCurrentValue();
    case EVehicleAttributeType::EngineBrakeEffect:
        return EngineBrakeEffect.GetCurrentValue();
    case EVehicleAttributeType::EngineRPMSpeedup:
        return EngineRPMSpeedup.GetCurrentValue();
    case EVehicleAttributeType::EngineRPMSlowdown:
        return EngineRPMSlowdown.GetCurrentValue();
    case EVehicleAttributeType::ChassisHeight:
        return ChassisHeight.GetCurrentValue();
    case EVehicleAttributeType::DragCoefficient:
        return DragCoefficient.GetCurrentValue();
    case EVehicleAttributeType::DownforceCoefficient:
        return DownforceCoefficient.GetCurrentValue();
    case EVehicleAttributeType::TopSpeed:
        return TopSpeed.GetCurrentValue();
    case EVehicleAttributeType::EnginePower:
        return EnginePower.GetCurrentValue();
    case EVehicleAttributeType::Weight:
        return Weight.GetCurrentValue();
    case EVehicleAttributeType::MaxWeight:
        return MaxWeight.GetCurrentValue();
    case EVehicleAttributeType::BulletResistance:
        return BulletResistance.GetCurrentValue();
    case EVehicleAttributeType::ExplosionResistance:
        return ExplosionResistance.GetCurrentValue();
    case EVehicleAttributeType::EnergyResistance:
        return EnergyResistance.GetCurrentValue();
    }

	return 0.0f;
}
