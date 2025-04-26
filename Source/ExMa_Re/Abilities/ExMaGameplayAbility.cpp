// Fill out your copyright notice in the Description page of Project Settings.


#include "Abilities/ExMaGameplayAbility.h"

#include "GameFramework/PlayerState.h"
#include "ExMa_Re/Weapons/ExMaProjectile.h"

#include "ExMa_Re/Vehicles/ExMa_RePawn.h"
#include "ExMa_Re/Items/WeaponActor.h"

#include "Kismet/KismetMathLibrary.h"
#include "ExMa_Re/ExMaGameplayTags.h"


UExMaGameplayAbility::UExMaGameplayAbility(const FObjectInitializer& ObjectInitializer)
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UExMaGameplayAbility::CreateStootLineTrace(TArray<FGameplayEffectSpecHandle> TraceEffects,
												FVector TraceStart,
												FVector TraceTarget,
												AActor* TraceInstigator)
{
	AWeaponActor* InstigatorWeapon = Cast<AWeaponActor>(TraceInstigator);

	if (!InstigatorWeapon)
	{
		return;
	}

	AExMa_RePawn* InstigatorOwner = Cast<AExMa_RePawn>(InstigatorWeapon->GetWeaponOwner());

	if (!InstigatorOwner)
	{
		return;
	}

	UWorld* World = Cast<UWorld>(GetWorld());

	//TODO: maybe will need LineTraceMultiple to make PiercingDamage
	if (World)
	{
		const TArray<const AActor*>& IgnoringActors = TArray<const AActor*>{ InstigatorWeapon, InstigatorOwner };

		FHitResult HitResult;
		FCollisionQueryParams CollisionParams;
		FCollisionResponseParams CollisionResponse;

		CollisionParams.AddIgnoredActors(IgnoringActors);
		//CollisionParams.AddIgnoredActor(TraceInstigator);

		if (World->LineTraceSingleByChannel(OUT HitResult, TraceStart, TraceTarget, ECollisionChannel::ECC_GameTraceChannel2, CollisionParams, CollisionResponse))
		{
			UE_LOG(LogTemplateVehicle, Warning, TEXT("UExMaGameplayAbility::CreateStootLineTrace: LineTraceHitSomething!"));

			AActor* HitActor = Cast<AActor>(HitResult.GetActor());

			if (!HitActor || HitActor == TraceInstigator|| HitActor == InstigatorWeapon->GetWeaponOwner())
				return;

			AExMa_RePawn* Target = Cast<AExMa_RePawn>(HitActor);

			if (!Target)
				return;

			ApplyTraceEffectsToTarget(TraceEffects, Target->GetAbilitySystemComponent());

			DrawDebugLine(World, TraceStart, HitResult.ImpactPoint, FColor::Red, false, -1.0f, 0, 2.0f);

			UE_LOG(LogTemplateVehicle, Warning, TEXT("UExMaGameplayAbility::CreateStootLineTrace: LineTraceHitActor!"));
		}
	}
}

AExMaProjectile* UExMaGameplayAbility::SpawnProjectile(TArray<FGameplayEffectSpecHandle> ProjectileEffects, 
														FVector ProjectileStart, 
														FVector ProjectileTarget, 
														AActor* Owner, 
														TSubclassOf<AExMaProjectile> ProjectileClass/*, FProjectileProperties ProjectileProperties*/)
{
	if (UWorld* World = Cast<UWorld>(GetWorld()))
	{
		const FGameplayAbilityActivationInfo ActivationInfo = GetCurrentActivationInfo();

		FVector Direction = ProjectileTarget - ProjectileStart;
		Direction.Normalize();
		FTransform Transform(Direction.ToOrientationRotator(), ProjectileStart);

		AExMaProjectile* Projectile = World->SpawnActorDeferred<AExMaProjectile>(ProjectileClass, Transform, Owner, Owner->GetInstigator());
		Projectile->TargetGrantedEffects = ProjectileEffects;
		//Projectile->TargetAreaEffectsSpec = GetAreaEffects();
		//Projectile->SetProjectileParams(ProjectileProperties);

		Projectile->FinishSpawning(Transform);
		return Projectile;
	}
	

	return nullptr;
}

void UExMaGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);

	//if (bActivateAbilityOnGranted)
	//{
	//	ActorInfo->AbilitySystemComponent->TryActivateAbility(Spec.Handle, false);
	//}
}

void UExMaGameplayAbility::OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnGiveAbility(ActorInfo, Spec);

	GiveAbilityEvent();
}

FGameplayTagRequirements UExMaGameplayAbility::GetTargetTagRequirements()
{
	return FGameplayTagRequirements();
}


TArray<FGameplayEffectSpecHandle> UExMaGameplayAbility::GetGrantedProjectileEffects_Implementation()
{
	return TArray<FGameplayEffectSpecHandle>();
}

void UExMaGameplayAbility::ApplyTraceEffectsToTarget(TArray<FGameplayEffectSpecHandle> TraceEffects, UAbilitySystemComponent* Target)
{
	for (const FGameplayEffectSpecHandle& EffectSpecHandle : TraceEffects)
	{
		float Damage = EffectSpecHandle.Data->GetSetByCallerMagnitude(ExMaGameplayTags::TAG_Ability_Damage);
		//if (Weapon && CurrentEnemyHitCount > 1 && Weapon->GetWeaponConfig().PassedEnemiesDamageMultiplier.Num() >= CurrentEnemyHitCount)
		//{
		//    Damage = Weapon->GetWeaponConfig().Damage * Weapon->GetWeaponConfig().PassedEnemiesDamageMultiplier[CurrentEnemyHitCount - 2];
		//}

		EffectSpecHandle.Data->SetSetByCallerMagnitude(ExMaGameplayTags::TAG_Ability_Damage, Damage);
		Target->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data);
	}
}

void UExMaGameplayAbility::ApplyBlustEffect(FVector Location)
{
}
