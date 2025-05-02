// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "ExMa_Re/Structs/TileStruct.h"
#include "ExMa_Re/Vehicles/VehicleParts/VehiclePart.h"

#include "Engine/StaticMesh.h"
#include "ExMa_Re/Structs/WeaponSlotInfo.h"

#include "VehiclePartDataAsset.generated.h"

UCLASS()
class EXMA_RE_API UVehiclePartDataAsset : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UVehiclePartDataAsset(const FObjectInitializer& ObjectInitializer);

	TSubclassOf<AVehiclePart> GetVehiclePartClass() { return VehiclePartClass; }

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Health = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxHealth = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Armor = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 MaxArmor = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Weight = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Cost = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float BulletResistance = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float ExplosionResistance = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float EnergyResistance = 0;

	//UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	//TArray<FTileStruct> WeaponSlots;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FWeaponSlotInfo> WeaponSlots;

#pragma region VehiclePart
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SFX")
	USoundBase* DeathFireSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SFX")
	USoundBase* DeathExplosionSound;
#pragma endregion SFX

#pragma region VehiclePart
	UPROPERTY(EditAnywhere, Category = "VFX|Particles")
	UParticleSystem* FireParticle;

	UPROPERTY(EditAnywhere, Category = "VFX|Particles")
	UParticleSystem* ExplosionParticle;

	UPROPERTY(EditAnywhere, Category = "VFX|ParticleSocket")
	FName FireSocketName;

	UPROPERTY(EditAnywhere, Category = "VFX|ParticleSocket")
	FName ExplosionSocketName;

	UPROPERTY(EditAnywhere, Category = "VFX|FireLight")
	float LightIntensity;

	UPROPERTY(EditAnywhere, Category = "VFX|FireLight")
	float LightRadius;

	UPROPERTY(EditAnywhere, Category = "VFX|FireLight")
	bool bIsLight;

	UPROPERTY(EditAnywhere, Category = "VFX|FireTransform")
	FVector FireDirection;

	UPROPERTY(EditAnywhere, Category = "VFX|FireTransform")
	FVector FireScale;

	UPROPERTY(EditAnywhere, Category = "VFX|FireTransform")
	FVector ExplosionScale;

	UPROPERTY(EditAnywhere, Category = "VFX|FireAngle")
	float RandomStartAngleMax;

	UPROPERTY(EditAnywhere, Category = "VFX|FireAngle")
	float RandomStartAngleMin;

	UPROPERTY(EditAnywhere, Category = "VFX|FireOscilator")
	float OscilatorSpeed;

	UPROPERTY(EditAnywhere, Category = "VFX|FireOscilator")
	bool bIsOscilate;

	UPROPERTY(EditAnywhere, Category = "VFX|FireSettings")
	bool bDistortionEmitterEnable;

	UPROPERTY(EditAnywhere, Category = "VFX|FireSettings")
	bool bSmokeEmitterEnable;

	UPROPERTY(EditAnywhere, Category = "VFX|TimeLine")
	class UCurveVector* VCurve;
#pragma endregion VFX

#if WITH_EDITOR
	virtual void PostInitProperties() override;
#endif
	
	virtual void PostLoad() override;


protected:
	//TODO: implement AVehiclePart class & set their static version here 
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<AVehiclePart> VehiclePartClass;

};
