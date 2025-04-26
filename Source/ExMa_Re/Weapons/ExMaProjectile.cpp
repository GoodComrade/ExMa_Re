// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/ExMaProjectile.h"

#include "AbilitySystemComponent.h"
#include "ExMa_Re/ExMaGameplayTags.h"

#include "ExMa_Re/Vehicles/ExMa_RePawn.h"
#include "ExMa_Re/Items/WeaponActor.h"

#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"

#include <Kismet/KismetSystemLibrary.h>

#include "AbilitySystemGlobals.h"
#include "GameFramework/ProjectileMovementComponent.h"
// Sets default values
AExMaProjectile::AExMaProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CollisionCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionSphere"));
	SetRootComponent(CollisionCapsule);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

	RadialForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("RadialForceComponent"));
	RadialForceComponent->SetupAttachment(CollisionCapsule);

    CollisionCapsule->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnSphereOverlapCharacter);
}

//void AExMaProjectile::SetProjectileParams(FProjectileProperties InProjectileProperties)
//{
//    ProjectileProperties = InProjectileProperties;
//
//    ProjectileMovementComponent->ProjectileGravityScale = 0;
//}

// Called when the game starts or when spawned
void AExMaProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AExMaProjectile::OnSphereOverlapCharacter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (OtherActor == GetOwner())
    {
        Destroy();
        return;
    }

    AWeaponActor* WeaponInstigator = Cast<AWeaponActor>(GetOwner());

    if(!WeaponInstigator)
    {
        Destroy();
        return;
    }

    AExMa_RePawn* Character = Cast<AExMa_RePawn>(WeaponInstigator->GetWeaponOwner());
    AExMa_RePawn* Target = Cast<AExMa_RePawn>(OtherActor);

    if (!Character || !Target || Character == Target)
    {
        Destroy();
        return;
    }

    if (!Target->IsDead())
    {
        ApplyEffectsToTarget(Target->GetAbilitySystemComponent());
        //ApplyAreaEffects(Target->GetActorLocation(), Target);
        ApplyBlustEffect(Target->GetActorLocation());
    }

    Destroy();
}

void AExMaProjectile::ApplyEffectsToTarget(UAbilitySystemComponent* Target)
{
    for (const FGameplayEffectSpecHandle& EffectSpecHandle : TargetGrantedEffects)
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

void AExMaProjectile::ApplyBlustEffect(FVector Location)
{
    //TODO: will need this code to implement explosion damage type
    //if (!Weapon || Weapon->GetWeaponConfig().BlustRadius <= 0) return;
    //
    //TArray<FOverlapResult> Overlaps;
    //GetWorld()->OverlapMultiByChannel(Overlaps, Location, FQuat::Identity, ECollisionChannel::ECC_Pawn, FCollisionShape::MakeSphere(ProjectileProperties.BlustRadius));
    //
    //TSet<AActor*> Targets;
    //
    //for (const FOverlapResult& Overlap : Overlaps)
    //{
    //    AActor* Target = Overlap.GetActor();
    //
    //    if (Targets.Contains(Target))
    //        continue;
    //
    //    if (CollisionCapsule->GetCollisionResponseToComponent(Overlap.GetComponent()) == ECollisionResponse::ECR_Ignore)
    //        continue;
    //
    //    Targets.Add(Target);
    //
    //    if (UAbilitySystemComponent* AbilitySystemComponent = UAbilitySystemGlobals::GetAbilitySystemComponentFromActor(Target))
    //    {
    //        AGoodHeroCharacter* Character = Cast<AGoodHeroCharacter>(GetInstigator());
    //        if (!Character) return;
    //
    //        if (AGoodHeroCharacter* CharacterTarget = Cast<AGoodHeroCharacter>(Target))
    //        {
    //            if (!Character->ShouldAttackTarget(CharacterTarget))
    //                continue;
    //        }
    //        for (const FGameplayEffectSpecHandle& EffectSpecHandle : TargetGrantedEffects)
    //        {
    //            float Damage = EffectSpecHandle.Data->GetSetByCallerMagnitude(GoodHeroGameplayTags::TAG_Ability_Damage);
    //            EffectSpecHandle.Data->SetSetByCallerMagnitude(GoodHeroGameplayTags::TAG_Ability_Damage, Damage);
    //            AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data);
    //        }
    //    }
    //    if (Target->GetClass()->ImplementsInterface(UBlustInteractor::StaticClass()))
    //    {
    //        IBlustInteractor* BlustInteractor = Cast<IBlustInteractor>(Target);
    //        BlustInteractor->Execute_OnBlust(Target, this);
    //    }
    //}
    //
    //OnBlustEffectEvent(Location);
}

// Called every frame
void AExMaProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

