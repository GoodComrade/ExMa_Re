// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/Texture2D.h"

#include "Engine/PointLight.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/TimelineComponent.h"
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

//------------Death VFX Settings----------------------//
private:

	UPROPERTY(EditAnywhere, Category = "VFX")
	UParticleSystem* FireParticle;

	UPROPERTY(EditAnywhere, Category = "VFX")
	UParticleSystem* ExplosionParticle;

	UPROPERTY(EditAnywhere, Category = "VFX")
	FName FireSocketname;

	UPROPERTY(EditAnywhere, Category = "VFX")
	FName ExplosionSocketname;

	UPROPERTY(EditAnywhere, Category = "VFX/|FireLight")
	float LightIntensity;

	UPROPERTY(EditAnywhere, Category = "VFX/|FireLight")
	float LightRadius;

	UPROPERTY(EditAnywhere, Category = "VFX/|FireLight")
	bool bIsLight;

	UPROPERTY(EditAnywhere, Category = "VFX/|FireTransform")
	FVector FireDirection;

	UPROPERTY(EditAnywhere, Category = "VFX/|FireTransform")
	FVector FireScale;

	UPROPERTY(EditAnywhere, Category = "VFX/|FireTransform")
	FVector ExplosionScale;

	UPROPERTY(EditAnywhere, Category = "VFX/|FireAngle")
	float RandomStartAngleMax;

	UPROPERTY(EditAnywhere, Category = "VFX/|FireAngle")
	float RandomStartAngleMin;

	UPROPERTY(EditAnywhere, Category = "VFX/|FireOscilator")
	float OscilatorSpeed;

	UPROPERTY(EditAnywhere, Category = "VFX/|FireOscilator")
	bool bIsOscilate;

	UPROPERTY(EditAnywhere, Category = "VFX/|FireSettings")
	bool bDistortionEmitterEnable;

	UPROPERTY(EditAnywhere, Category = "VFX/|FireSettings")
	bool bSmokeEmitterEnable;

//------------Death VFX Settings End----------------------//
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//virtual void OnConstruction(const FTransform& Transform) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn))
	UVehiclePartDataAsset* VehiclePartData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* VehiclePartMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VFX")
	UParticleSystemComponent* FireParticleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VFX")
	UPointLightComponent* FireLightPointComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VFX")
	UParticleSystemComponent* ExplosionParticleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VFX/|TimeLine")
	UTimelineComponent* EffectTimelineComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UFUNCTION()
	void SetupDeathVFX();

	UFUNCTION()
	void ProcessDeathVFX();

	//Declare our delegate function to be binded with TimelineUpdate
	FOnTimelineVector VectorUpdate{};

	UPROPERTY(EditAnywhere, Category = "TimeLine")
	class UCurveVector* VCurve;

	UFUNCTION()
	void TimelineUpdate(FVector DirVector);
};
