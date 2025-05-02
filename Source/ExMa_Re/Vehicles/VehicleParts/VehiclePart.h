// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Texture2D.h"

#include "Engine/PointLight.h"
#include "Particles/ParticleSystemComponent.h"

#include "Components/PointLightComponent.h"
#include "Components/TimelineComponent.h"
#include "Components/AudioComponent.h"

#include "Sound/SoundBase.h"

#include "Curves/CurveVector.h"

#include "VehiclePart.generated.h"

class UVehiclePartDataAsset;
class UStaticMeshComponent;
class UStaticMesh;

UCLASS()
class EXMA_RE_API AVehiclePart : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVehiclePart();

	UFUNCTION(BlueprintCallable)
	UVehiclePartDataAsset* GetVehiclePartData() const { return VehiclePartData; };

	UFUNCTION(BlueprintCallable)
	UStaticMeshComponent* GetVehicleStaticMeshComponent() const { return VehiclePartMesh; };

	UFUNCTION(BlueprintCallable)
	void SetVehiclePartData(UVehiclePartDataAsset* DataToSet);

	UFUNCTION(BlueprintCallable)
	void SetVehiclePartMesh(UStaticMesh* MeshToSet);

	UFUNCTION(BlueprintCallable)
	void ProcessDeathLogic(UTexture2D* InDeathTexture);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn))
	UVehiclePartDataAsset* VehiclePartData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* VehiclePartMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SFX")
	UAudioComponent* DeathFireSoundComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "SFX")
	UAudioComponent* DeathExplosionSoundComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VFX")
	UPointLightComponent* FireLightPointComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VFX")
	UParticleSystemComponent* FireParticleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VFX")
	UParticleSystemComponent* ExplosionParticleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TimeLine")
	UTimelineComponent* EffectTimelineComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
	void SetupDeathSFX();

	UFUNCTION()
	void ProcessExplosionSFX();

	UFUNCTION()
	void ProcessFireSFX();

	UFUNCTION()
	void SetupDeathVFX();

	UFUNCTION()
	void ProcessDeathVFX();

	//Declare our delegate function to be binded with TimelineUpdate
	FOnTimelineVector VectorUpdate{};

	UFUNCTION()
	void TimelineUpdate(FVector DirVector);

	FTimerHandle FireAudioDelayHandle;
};
