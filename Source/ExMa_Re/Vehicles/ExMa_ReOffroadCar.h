// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ExMa_Re/Vehicles/ExMa_RePawn.h"

#include "Engine/Texture2D.h"

#include "ExMa_ReOffroadCar.generated.h"

/**
 *  Offroad car wheeled vehicle implementation
 */
UCLASS()
class EXMA_RE_API AExMa_ReOffroadCar : public AExMa_RePawn
{
	GENERATED_BODY()
	
	/** Chassis static mesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Meshes, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Chassis;

	/** FL Tire static mesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Meshes, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TireFrontLeft;

	/** FR Tire static mesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Meshes, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TireFrontRight;

	/** RL Tire static mesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Meshes, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TireRearLeft;

	/** RR Tire static mesh */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Meshes, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TireRearRight;

public:

	AExMa_ReOffroadCar();

protected:
	virtual void BeginPlay() override;

protected:
	virtual void OnDeath() override;

private:
	void ProcessDetachWheels();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* CarDeathColorTexture;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* TruckDeathColorTexture;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UTexture2D* WeaponDeathColorTexture;
};
