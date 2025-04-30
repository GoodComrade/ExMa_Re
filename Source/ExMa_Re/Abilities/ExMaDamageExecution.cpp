// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/ExMaDamageExecution.h"
#include "AbilitySystemComponent.h"

#include "ExMa_Re/Vehicles/ExMa_RePawn.h"
#include "ExMa_Re/Vehicles/ExMa_VehicleAttributes.h"

#include "ExMa_Re/Items/WeaponActor.h"
#include "ExMa_Re/Weapons/ExMa_WeaponAttributes.h"

#include "ExMa_Re/ExMaGameplayTags.h"

struct ExMaDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Damage);

	ExMaDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UExMa_WeaponAttributes, Damage, Source, true);
	}
};

static const ExMaDamageStatics& DamageStatics()
{
	static ExMaDamageStatics Statics;
	return Statics;
}

UExMaDamageExecution::UExMaDamageExecution()
{
	RelevantAttributesToCapture.Add(DamageStatics().DamageDef);
}

void UExMaDamageExecution::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, OUT FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();

	AActor* SourceActor = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->GetAvatarActor() : nullptr;
	AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->GetAvatarActor() : nullptr;

	if (SourceActor == TargetActor)
		return;

	AWeaponActor* Weapon = Cast<AWeaponActor>(SourceActor);
	if (Weapon)
	{
		if (Weapon->GetWeaponOwner() == TargetActor)
			return;
	}

	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	// Gather the tags from the source and target as that can affect which buffs should be used
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	float Damage = 0.0f;

	Damage += Spec.GetSetByCallerMagnitude(ExMaGameplayTags::TAG_Ability_Damage, false, 0.0f);

	if (Damage > 0.0f)
	{
		// Apply a damage modifier, this gets turned into - health on the target
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UExMa_VehicleAttributes::GetIncomeDamageAttribute(), EGameplayModOp::Additive, Damage));

		// Apply Weapon deterioration
		OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(UExMa_WeaponAttributes::GetHealthAttribute(), EGameplayModOp::Additive, -Damage));
	}

	// Some effects can decrease their damage on every executions.
	float DamageDecrease = Spec.GetSetByCallerMagnitude(ExMaGameplayTags::TAG_Ability_Damage_Decrease, false, 0.0f);
	if (DamageDecrease > 0)
	{
		Damage -= DamageDecrease;

		if (FGameplayEffectSpec* PreExecuteSpec = ExecutionParams.GetOwningSpecForPreExecuteMod())
		{
			PreExecuteSpec->SetSetByCallerMagnitude(ExMaGameplayTags::TAG_Ability_Damage, Damage);
		}
	}

	float DamageFactor = Spec.GetSetByCallerMagnitude(ExMaGameplayTags::TAG_Ability_Damage_Factor, false, 0.0f);
	if (DamageFactor > 0)
	{
		Damage *= DamageFactor;

		if (FGameplayEffectSpec* PreExecuteSpec = ExecutionParams.GetOwningSpecForPreExecuteMod())
		{
			PreExecuteSpec->SetSetByCallerMagnitude(ExMaGameplayTags::TAG_Ability_Damage, Damage);
		}
	}
}
