// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicles/VehicleParts/VehiclePart.h"
#include "Engine/Texture2D.h"
#include "ExMa_Re/DataAssets/Vehicles/VehicleParts/VehiclePartDataAsset.h"

#include "Engine/PointLight.h"
#include "Particles/ParticleSystemComponent.h"

#include "Components/LightComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/TimelineComponent.h"
#include "Components/AudioComponent.h"

// Sets default values
AVehiclePart::AVehiclePart()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	VehiclePartMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VehiclePartMesh"));
	VehiclePartMesh->SetupAttachment(RootComponent);

	DeathFireSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("FireSound"));
	DeathFireSoundComponent->SetupAttachment(VehiclePartMesh);
	DeathFireSoundComponent->bAutoActivate = false;
	DeathFireSoundComponent->bAllowSpatialization = true;
	DeathFireSoundComponent->bOverrideAttenuation = true;
	DeathFireSoundComponent->AttenuationOverrides.bAttenuate = true;
	DeathFireSoundComponent->AttenuationOverrides.AttenuationShape = EAttenuationShape::Sphere;
	DeathFireSoundComponent->AttenuationOverrides.AttenuationShapeExtents = FVector(600.f);
	DeathFireSoundComponent->AttenuationOverrides.FalloffDistance = 6000.f;

	DeathExplosionSoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("ExplosionSound"));
	DeathExplosionSoundComponent->SetupAttachment(VehiclePartMesh);
	DeathExplosionSoundComponent->bAutoActivate = false;
	DeathExplosionSoundComponent->bAllowSpatialization = true;
	DeathExplosionSoundComponent->bOverrideAttenuation = true;
	DeathExplosionSoundComponent->AttenuationOverrides.bAttenuate = true;
	DeathExplosionSoundComponent->AttenuationOverrides.AttenuationShape = EAttenuationShape::Sphere;
	DeathExplosionSoundComponent->AttenuationOverrides.AttenuationShapeExtents = FVector(600.f);
	DeathExplosionSoundComponent->AttenuationOverrides.FalloffDistance = 6000.f;

	FireLightPointComponent = CreateDefaultSubobject<UPointLightComponent>(TEXT("FireLightPoint"));
	FireLightPointComponent->SetupAttachment(VehiclePartMesh);

	FireParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("FireParticles"));
	FireParticleComponent->SetupAttachment(VehiclePartMesh);
	FireParticleComponent->bAutoActivate = false;

	ExplosionParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ExplosionParticles"));
	ExplosionParticleComponent->SetupAttachment(VehiclePartMesh);
	ExplosionParticleComponent->bAutoActivate = false;

	EffectTimelineComponent = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimelineComponent"));
	VectorUpdate.BindUFunction(this, FName("TimelineUpdate"));

	VehiclePartData = nullptr;
}

void AVehiclePart::SetVehiclePartData(UVehiclePartDataAsset* DataToSet)
{
	if (!DataToSet)
	{
		UE_LOG(LogTemp, Warning, TEXT("AVehiclePart::SetVehiclePartData: DataToSet == nullptr"));
	}

	VehiclePartData = DataToSet;

	SetupDeathSFX();
	SetupDeathVFX();
}

void AVehiclePart::SetVehiclePartMesh(UStaticMesh* MeshToSet)
{
	VehiclePartMesh->SetStaticMesh(MeshToSet);
}

void AVehiclePart::ProcessDeathLogic(UTexture2D* InDeathTexture)
{
	if (!VehiclePartMesh)
	{
		UE_LOG(LogTemp, Warning, TEXT("AVehiclePart::ProcessDeathLogic: VehiclePartMesh == nullptr"));
		return;
	}

	if (VehiclePartData->VCurve)
	{
		EffectTimelineComponent->AddInterpVector(VehiclePartData->VCurve, VectorUpdate, FName("Dir Vector"));
		ProcessExplosionSFX();
		ProcessDeathVFX();
	}

	int32 MaterialCount = VehiclePartMesh->GetNumMaterials();

	for (int32 Index = 0; Index < MaterialCount; ++Index)
	{
		UMaterialInterface* BaseMaterial = VehiclePartMesh->GetMaterial(Index);
		if (!BaseMaterial) continue;

		UMaterialInstanceDynamic* DynMaterial = VehiclePartMesh->CreateAndSetMaterialInstanceDynamicFromMaterial(Index, BaseMaterial);
		if (!DynMaterial) continue;

		DynMaterial->SetTextureParameterValue("TargetColor", InDeathTexture);
	}

	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

	VehiclePartMesh->SetCollisionProfileName(FName("BlockAll"));

	VehiclePartMesh->RecreatePhysicsState();

	VehiclePartMesh->SetEnableGravity(true);
	VehiclePartMesh->SetUseCCD(true);
	VehiclePartMesh->SetSimulatePhysics(true);

	FVector UpwardImpulse(0.0f, 0.0f, 800.0f);
	VehiclePartMesh->AddImpulse(UpwardImpulse, NAME_None, true);

	UE_LOG(LogTemp, Warning, TEXT("AVehiclePart::ProcessDeathLogic: VehiclePartMesh Detached"));

	//SetLifeSpan(10.0f);
}

// Called when the game starts or when spawned
void AVehiclePart::BeginPlay()
{
	Super::BeginPlay();
}

//void AVehiclePart::OnConstruction(const FTransform& Transform)
//{
//	Super::OnConstruction(Transform);
//
//	
//}

// Called every frame
void AVehiclePart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AVehiclePart::SetupDeathSFX()
{
	if (DeathExplosionSoundComponent && VehiclePartData->DeathExplosionSound)
		DeathExplosionSoundComponent->SetSound(VehiclePartData->DeathExplosionSound);

	if (DeathFireSoundComponent && VehiclePartData->DeathFireSound)
		DeathFireSoundComponent->SetSound(VehiclePartData->DeathFireSound);
}

void AVehiclePart::ProcessExplosionSFX()
{
	if (DeathExplosionSoundComponent)
		DeathExplosionSoundComponent->Play();

	GetWorld()->GetTimerManager().SetTimer(FireAudioDelayHandle, this, &AVehiclePart::ProcessFireSFX, 2.5f, false);
}

void AVehiclePart::ProcessFireSFX()
{
	if (DeathFireSoundComponent)
		DeathFireSoundComponent->Play();
}

void AVehiclePart::SetupDeathVFX()
{
	/* Setup death VFX from data asset */
	if (!VehiclePartData)
	{
		UE_LOG(LogTemp, Warning, TEXT("AVehiclePart::SetupDeathVFX: VehiclePartMesh == nullptr"));
		return;
	}

	FireLightPointComponent->SetIntensity(VehiclePartData->LightIntensity);
	FireLightPointComponent->SetAttenuationRadius(VehiclePartData->LightRadius);

	FVector FireLocation = VehiclePartMesh->GetSocketLocation(VehiclePartData->FireSocketName);
	FireParticleComponent->SetWorldLocation(FireLocation);
	FireParticleComponent->SetTemplate(VehiclePartData->FireParticle);
	FireParticleComponent->SetWorldScale3D(VehiclePartData->FireScale);

	if (!VehiclePartData->ExplosionParticle)
		return;

	FTransform BaseExplosionTransform = VehiclePartMesh->GetSocketTransform(VehiclePartData->ExplosionSocketName);
	FVector ExplosionLocation = VehiclePartMesh->GetSocketLocation(VehiclePartData->ExplosionSocketName);
	FTransform ExplosionTransform;

	ExplosionTransform.SetLocation(BaseExplosionTransform.GetLocation());
	ExplosionTransform.SetRotation(BaseExplosionTransform.GetRotation());
	ExplosionTransform.SetScale3D(VehiclePartData->ExplosionScale);

	ExplosionParticleComponent->SetWorldTransform(ExplosionTransform);
	ExplosionParticleComponent->SetWorldLocation(ExplosionLocation);
	ExplosionParticleComponent->SetTemplate(VehiclePartData->ExplosionParticle);
}

void AVehiclePart::ProcessDeathVFX()
{
	FireLightPointComponent->SetVisibility(VehiclePartData->bIsLight);

	if (VehiclePartData->ExplosionParticle && ExplosionParticleComponent)
		ExplosionParticleComponent->Activate();

	FireParticleComponent->SetEmitterEnable(FName("smoke"), VehiclePartData->bSmokeEmitterEnable);
	FireParticleComponent->SetEmitterEnable(FName("Distortion"), VehiclePartData->bDistortionEmitterEnable);
	FireParticleComponent->Activate();

	EffectTimelineComponent->SetPlayRate(VehiclePartData->OscilatorSpeed);
	EffectTimelineComponent->Play();
}

void AVehiclePart::TimelineUpdate(FVector DirVector)
{
	if (!VehiclePartData)
	{
		UE_LOG(LogTemp, Warning, TEXT("AVehiclePart::TimelineUpdate: VehiclePartMesh == nullptr"));
		return;
	}

	float RandDirection = FMath::RandRange(VehiclePartData->RandomStartAngleMin, VehiclePartData->RandomStartAngleMax);
	FVector RandomVector = FVector(RandDirection, RandDirection, 0);

	FVector DefaultVector = (VehiclePartData->FireDirection + RandomVector).GetSafeNormal();
	FVector OscilatedVector = (DirVector + RandomVector).GetSafeNormal();

	FireParticleComponent->SetVectorParameter(FName("dir"), VehiclePartData->bIsOscilate ? OscilatedVector : DefaultVector);
}

