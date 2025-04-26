// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ExMa_Re/Weapons/WeaponAttributeType.h"
#include "Abilities/ExMaGameplayAbility.h"
#include "WeaponGameplayAbility.generated.h"

class UGameplayEffect;
class AWeaponActor;

UCLASS()
class EXMA_RE_API UWeaponGameplayAbility : public UExMaGameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	float GetWeaponAttribute(EWeaponAttributeType WeaponAttribute) const;

	//UFUNCTION(BlueprintCallable)
	//static float ModifyAttributes(EWeaponAttributeType WeaponAttribute, float WeaponVal, float CharacterVal);

	//virtual TArray<FAreaEffectSpec> GetAreaEffects() override;

	//virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const;
    //
	//virtual bool CommitAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) override;
    //
	//UFUNCTION(BlueprintCallable)
	//virtual bool OwnerCharacterCanActivateAbility() const;

protected:
    //virtual FGameplayTagRequirements GetTargetTagRequirements() override;

    //UFUNCTION(BlueprintCallable)
    //void AttributeCalculations();

    UPROPERTY(BlueprintReadWrite)
    FGameplayEffectSpecHandle DamageEffectSpec;

    virtual TArray<FGameplayEffectSpecHandle> GetGrantedProjectileEffects_Implementation() override;

    //UPROPERTY(BlueprintReadWrite)
    //int32 BurstSize = 0;

    // Tag requirements to weapon owner character to activate ability
    //UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Tags")
    //FGameplayTagRequirements CharacterActivateAbilityTagRequirements;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
    TSubclassOf<UGameplayEffect> DamageEffectSpecHandle;

    UPROPERTY(BlueprintReadWrite)
    AWeaponActor* AbillityWeapon;
};
