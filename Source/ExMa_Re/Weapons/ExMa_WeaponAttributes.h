// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystemComponent.h"
#include "CoreMinimal.h"
#include "WeaponAttributeType.h"
#include "ExMa_WeaponAttributes.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, Attribute)                                   \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(Attribute);                                      \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(Attribute);                                      \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(Attribute);                                     \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, Attribute);

UCLASS()
class EXMA_RE_API UExMa_WeaponAttributes : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly, Category = Weapon)
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(UExMa_WeaponAttributes, Damage);

	UPROPERTY(BlueprintReadOnly, Category = Weapon)
	FGameplayAttributeData AttackCost;
	ATTRIBUTE_ACCESSORS(UExMa_WeaponAttributes, AttackCost);

	UPROPERTY(BlueprintReadOnly, Category = Weapon)
	FGameplayAttributeData Cooldown;
	ATTRIBUTE_ACCESSORS(UExMa_WeaponAttributes, Cooldown);

	UPROPERTY(BlueprintReadOnly, Category = Weapon)
	FGameplayAttributeData ShootDelay;
	ATTRIBUTE_ACCESSORS(UExMa_WeaponAttributes, ShootDelay);

	UPROPERTY(BlueprintReadOnly, Category = Weapon)
	FGameplayAttributeData ReloadTime;
	ATTRIBUTE_ACCESSORS(UExMa_WeaponAttributes, ReloadTime);

	UPROPERTY(BlueprintReadOnly, Category = Weapon)
	FGameplayAttributeData Spread;
	ATTRIBUTE_ACCESSORS(UExMa_WeaponAttributes, Spread);

	UPROPERTY(BlueprintReadOnly, Category = Weapon)
	FGameplayAttributeData MaxBulletsCount;
	ATTRIBUTE_ACCESSORS(UExMa_WeaponAttributes, MaxBulletsCount);

	UPROPERTY(BlueprintReadOnly, Category = Weapon)
	FGameplayAttributeData CurrentMagazineAmount;
	ATTRIBUTE_ACCESSORS(UExMa_WeaponAttributes, CurrentMagazineAmount);

	UPROPERTY(BlueprintReadOnly, Category = Weapon)
	FGameplayAttributeData MagazineSize;
	ATTRIBUTE_ACCESSORS(UExMa_WeaponAttributes, MagazineSize);

	//UPROPERTY(BlueprintReadOnly, Category = Weapon)
	//FGameplayAttributeData BurstSize;
	//ATTRIBUTE_ACCESSORS(UExMa_WeaponAttributes, BurstSize);

	UPROPERTY(BlueprintReadOnly, Category = Weapon)
	FGameplayAttributeData MinRange;
	ATTRIBUTE_ACCESSORS(UExMa_WeaponAttributes, MinRange);

	UPROPERTY(BlueprintReadOnly, Category = Weapon)
	FGameplayAttributeData MaxRange;
	ATTRIBUTE_ACCESSORS(UExMa_WeaponAttributes, MaxRange);

	//UPROPERTY(BlueprintReadOnly, Category = Weapon)
	//FGameplayAttributeData MinBulletsInShot;
	//ATTRIBUTE_ACCESSORS(UExMa_WeaponAttributes, MinBulletsInShot);
	//
	//UPROPERTY(BlueprintReadOnly, Category = Weapon)
	//FGameplayAttributeData MaxBulletsInShot;
	//ATTRIBUTE_ACCESSORS(UExMa_WeaponAttributes, MaxBulletsInShot);

	UPROPERTY(BlueprintReadOnly, Category = Weapon)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UExMa_WeaponAttributes, Health);

	UPROPERTY(BlueprintReadOnly, Category = Weapon)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UExMa_WeaponAttributes, MaxHealth);

	//UPROPERTY(BlueprintReadOnly, Category = Weapon)
	//FGameplayAttributeData BurstDelay;
	//ATTRIBUTE_ACCESSORS(UExMa_WeaponAttributes, BurstDelay);
	//
	//UPROPERTY(BlueprintReadOnly, Category = Weapon)
	//FGameplayAttributeData ProjectileSpeed;
	//ATTRIBUTE_ACCESSORS(UExMa_WeaponAttributes, ProjectileSpeed);
	//
	//UPROPERTY(BlueprintReadOnly, Category = Weapon)
	//FGameplayAttributeData ProjectileGravityMultiplier;
	//ATTRIBUTE_ACCESSORS(UExMa_WeaponAttributes, ProjectileGravityMultiplier);
	//
	//UPROPERTY(BlueprintReadOnly, Category = Weapon)
	//FGameplayAttributeData AimType;
	//ATTRIBUTE_ACCESSORS(UExMa_WeaponAttributes, AimType);
	//
	//UPROPERTY(BlueprintReadOnly, Category = Weapon)
	//FGameplayAttributeData BlustRadius;
	//ATTRIBUTE_ACCESSORS(UExMa_WeaponAttributes, BlustRadius);

	UPROPERTY(BlueprintReadOnly, Category = Weapon)
	FGameplayAttributeData AimTime;
	ATTRIBUTE_ACCESSORS(UExMa_WeaponAttributes, AimTime);

	UFUNCTION(BlueprintCallable)
	float GetAttribute(EWeaponAttributeType IWeaponAttributeType) const;
};
