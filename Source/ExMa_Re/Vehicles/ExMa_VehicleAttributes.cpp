// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicles/ExMa_VehicleAttributes.h"

void UExMa_VehicleAttributes::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
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
    case EVehicleAttributeType::BulletResistance:
        return BulletResistance.GetCurrentValue();
    case EVehicleAttributeType::ExplosionResistance:
        return ExplosionResistance.GetCurrentValue();
    case EVehicleAttributeType::EnergyResistance:
        return EnergyResistance.GetCurrentValue();
    }

	return 0.0f;
}
