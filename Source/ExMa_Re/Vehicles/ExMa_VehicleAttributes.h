// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemComponent.h"
#include "CoreMinimal.h"
#include "VehicleAttributeType.h"
#include "ExMa_VehicleAttributes.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, Attribute)                                   \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Attribute);                                      \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Attribute);                                      \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Attribute);                                     \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, Attribute);

UCLASS()
class EXMA_RE_API UExMa_VehicleAttributes : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly, Category = Vehicle)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UExMa_VehicleAttributes, Health);

	UPROPERTY(BlueprintReadOnly, Category = Vehicle)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UExMa_VehicleAttributes, MaxHealth);

	UPROPERTY(BlueprintReadOnly, Category = Vehicle)
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UExMa_VehicleAttributes, Armor);

	UPROPERTY(BlueprintReadOnly, Category = Vehicle)
	FGameplayAttributeData GasTankSize;
	ATTRIBUTE_ACCESSORS(UExMa_VehicleAttributes, GasTankSize);

	UPROPERTY(BlueprintReadOnly, Category = VehicleEngine)
	FGameplayAttributeData MaxTorque;
	ATTRIBUTE_ACCESSORS(UExMa_VehicleAttributes, MaxTorque);

	UPROPERTY(BlueprintReadOnly, Category = VehicleEngine)
	FGameplayAttributeData MaxRPM;
	ATTRIBUTE_ACCESSORS(UExMa_VehicleAttributes, MaxRPM);

	UPROPERTY(BlueprintReadOnly, Category = VehicleEngine)
	FGameplayAttributeData EngineIdleRPM;
	ATTRIBUTE_ACCESSORS(UExMa_VehicleAttributes, EngineIdleRPM);

	UPROPERTY(BlueprintReadOnly, Category = VehicleEngine)
	FGameplayAttributeData EngineBrakeEffect;
	ATTRIBUTE_ACCESSORS(UExMa_VehicleAttributes, EngineBrakeEffect);

	UPROPERTY(BlueprintReadOnly, Category = VehicleEngine)
	FGameplayAttributeData EngineRPMSpeedup;
	ATTRIBUTE_ACCESSORS(UExMa_VehicleAttributes, EngineRPMSpeedup);

	UPROPERTY(BlueprintReadOnly, Category = VehicleEngine)
	FGameplayAttributeData EngineRPMSlowdown;
	ATTRIBUTE_ACCESSORS(UExMa_VehicleAttributes, EngineRPMSlowdown);

	UPROPERTY(BlueprintReadOnly, Category = VehicleEngine)
	FGameplayAttributeData TopSpeed;
	ATTRIBUTE_ACCESSORS(UExMa_VehicleAttributes, TopSpeed);

	UPROPERTY(BlueprintReadOnly, Category = VehicleEngine)
	FGameplayAttributeData EnginePower;
	ATTRIBUTE_ACCESSORS(UExMa_VehicleAttributes, EnginePower);

	UPROPERTY(BlueprintReadOnly, Category = VehicleChasis)
	FGameplayAttributeData ChassisHeight;
	ATTRIBUTE_ACCESSORS(UExMa_VehicleAttributes, ChassisHeight);

	UPROPERTY(BlueprintReadOnly, Category = VehicleChasis)
	FGameplayAttributeData DragCoefficient;
	ATTRIBUTE_ACCESSORS(UExMa_VehicleAttributes, DragCoefficient);

	UPROPERTY(BlueprintReadOnly, Category = VehicleChasis)
	FGameplayAttributeData DownforceCoefficient;
	ATTRIBUTE_ACCESSORS(UExMa_VehicleAttributes, DownforceCoefficient);

	UPROPERTY(BlueprintReadOnly, Category = Vehicle)
	FGameplayAttributeData Weight;
	ATTRIBUTE_ACCESSORS(UExMa_VehicleAttributes, Weight);

	UPROPERTY(BlueprintReadOnly, Category = Vehicle)
	FGameplayAttributeData BulletResistance;
	ATTRIBUTE_ACCESSORS(UExMa_VehicleAttributes, BulletResistance);

	UPROPERTY(BlueprintReadOnly, Category = Vehicle)
	FGameplayAttributeData ExplosionResistance;
	ATTRIBUTE_ACCESSORS(UExMa_VehicleAttributes, ExplosionResistance);

	UPROPERTY(BlueprintReadOnly, Category = Vehicle)
	FGameplayAttributeData EnergyResistance;
	ATTRIBUTE_ACCESSORS(UExMa_VehicleAttributes, EnergyResistance);

	UFUNCTION(BlueprintCallable)
	float GetAttribute(EVehicleAttributeType IVehicleAttributeType) const;
};
