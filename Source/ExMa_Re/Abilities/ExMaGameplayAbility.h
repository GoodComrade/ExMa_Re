// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"

#include "ExMa_Re/Weapons/WeaponAttributeType.h"
#include "ExMa_Re/Weapons/ExMaProjectile.h"

#include "ExMaGameplayAbility.generated.h"

class UGameplayEffect;
class AWeaponActor;
enum class EWeaponAttributeType : uint8;

UCLASS()
class EXMA_RE_API UExMaGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UExMaGameplayAbility(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, Category = "Ability")
	virtual void CreateStootLineTrace(TArray<FGameplayEffectSpecHandle> TraceEffects,
										FVector TraceStart,
										FVector TraceTarget,
										AActor* TraceInstigator);

	UFUNCTION(BlueprintCallable, Category = "Ability", Meta = (DeterminesOutputType = "ProjectileClass"))
	virtual AExMaProjectile* SpawnProjectile(TArray<FGameplayEffectSpecHandle> ProjectileEffects, 
											FVector ProjectileStart, 
											FVector ProjectileTarget, 
											AActor* Owner, 
											TSubclassOf<AExMaProjectile> ProjectileClass/*, FProjectileProperties ProjectileProperties*/);

	virtual void OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;

	UFUNCTION(BlueprintImplementableEvent)
	void GiveAbilityEvent();

	UFUNCTION(BlueprintPure)
	virtual FGameplayTagRequirements GetTargetTagRequirements();

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bActivateAbilityOnGranted = false;

protected:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Effects")
	TArray<FGameplayEffectSpecHandle> GetGrantedProjectileEffects();
	virtual TArray<FGameplayEffectSpecHandle> GetGrantedProjectileEffects_Implementation();

	UFUNCTION(BlueprintCallable)
	void ApplyTraceEffectsToTarget(TArray<FGameplayEffectSpecHandle> TraceEffects, UAbilitySystemComponent* Target);

	UFUNCTION(BlueprintCallable)
	void ApplyBlustEffect(FVector Location);
};
