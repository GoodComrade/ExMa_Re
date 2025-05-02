// Fill out your copyright notice in the Description page of Project Settings.


#include "Vehicles/VehicleParts/VehiclePart.h"
#include "Engine/Texture2D.h"
#include "ExMa_Re/DataAssets/Vehicles/VehicleParts/VehiclePartDataAsset.h"

#include "Engine/PointLight.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/LightComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/TimelineComponent.h"

// Sets default values
AVehiclePart::AVehiclePart()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	VehiclePartMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VehiclePartMesh"));
	VehiclePartMesh->SetupAttachment(RootComponent);

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

	/* Setup death VFX from data asset */

	//Setup particles
	FireParticle = VehiclePartData->FireParticle;
	ExplosionParticle = VehiclePartData->ExplosionParticle;

	//Setup Sockets
	FireSocketname = VehiclePartData->FireSocketname;
	ExplosionSocketname = VehiclePartData->ExplosionSocketname;

	//Setup FireLight
	LightIntensity = VehiclePartData->LightIntensity;
	LightRadius = VehiclePartData->LightRadius;
	bIsLight = VehiclePartData->bIsLight;

	//Setup FireTransform
	FireDirection = VehiclePartData->FireDirection;
	FireScale = VehiclePartData->FireScale;
	ExplosionScale = VehiclePartData->ExplosionScale;

	//Setup FireAngle
	RandomStartAngleMax = VehiclePartData->RandomStartAngleMax;
	RandomStartAngleMin = VehiclePartData->RandomStartAngleMin;

	//Setup FireOscilator
	OscilatorSpeed = VehiclePartData->OscilatorSpeed;
	bIsOscilate = VehiclePartData->bIsOscilate;

	//Setup FireEmitters
	bDistortionEmitterEnable = VehiclePartData->bDistortionEmitterEnable;
	bSmokeEmitterEnable = VehiclePartData->bSmokeEmitterEnable;

	//Setup TimeLine
	VCurve = VehiclePartData->VCurve;

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

	if (VCurve)
	{
		EffectTimelineComponent->AddInterpVector(VCurve, VectorUpdate, FName("Dir Vector"));
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

void AVehiclePart::SetupDeathVFX()
{
	FireLightPointComponent->SetIntensity(LightIntensity);
	FireLightPointComponent->SetAttenuationRadius(LightRadius);

	FVector FireLocation = VehiclePartMesh->GetSocketLocation(FireSocketname);
	FireParticleComponent->SetWorldLocation(FireLocation);
	FireParticleComponent->SetTemplate(FireParticle);
	FireParticleComponent->SetWorldScale3D(FireScale);

	FTransform BaseExplosionTransform = VehiclePartMesh->GetSocketTransform(ExplosionSocketname);
	FVector ExplosionLocation = VehiclePartMesh->GetSocketLocation(ExplosionSocketname);
	FTransform ExplosionTransform;

	ExplosionTransform.SetLocation(BaseExplosionTransform.GetLocation());
	ExplosionTransform.SetRotation(BaseExplosionTransform.GetRotation());
	ExplosionTransform.SetScale3D(ExplosionScale);

	ExplosionParticleComponent->SetWorldTransform(ExplosionTransform);
	ExplosionParticleComponent->SetWorldLocation(ExplosionLocation);
	ExplosionParticleComponent->SetTemplate(ExplosionParticle);
}

void AVehiclePart::ProcessDeathVFX()
{
	FireLightPointComponent->SetVisibility(bIsLight);

	ExplosionParticleComponent->Activate();

	FireParticleComponent->SetEmitterEnable(FName("smoke"), bSmokeEmitterEnable);
	FireParticleComponent->SetEmitterEnable(FName("Distortion"), bDistortionEmitterEnable);
	FireParticleComponent->Activate();

	EffectTimelineComponent->SetPlayRate(OscilatorSpeed);
	EffectTimelineComponent->Play();
}

void AVehiclePart::TimelineUpdate(FVector DirVector)
{
	float RandDirection = FMath::RandRange(RandomStartAngleMin, RandomStartAngleMax);
	FVector RandomVector = FVector(RandDirection, RandDirection, 0);

	FVector DefaultVector = (FireDirection + RandomVector).GetSafeNormal();
	FVector OscilatedVector = (DirVector + RandomVector).GetSafeNormal();

	FireParticleComponent->SetVectorParameter(FName("dir"), bIsOscilate ? OscilatedVector : DefaultVector);
}

