// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VehicleSpawner.generated.h"

USTRUCT(BlueprintType)
struct FSpawnableProperties
{
    GENERATED_BODY()

public:
    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FName VehicleBase;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FName VehicleCabin;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FName VehicleBody;

    UPROPERTY(BlueprintReadWrite, EditAnywhere)
    FName VehicleWeapon;
};

UCLASS()
class EXMA_RE_API AVehicleSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVehicleSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
    UFUNCTION()
    void SpawnVehicles();

public:
    UPROPERTY(EditAnywhere)
    TArray<FSpawnableProperties> VehiclesToSpawn;

    UPROPERTY(EditAnywhere)
    UDataTable* VehicleDT = nullptr;

    UPROPERTY(EditAnywhere)
    UDataTable* VehicleCarBodyDT = nullptr;

    UPROPERTY(EditAnywhere)
    UDataTable* VehicleTruckCabinDT = nullptr;

    UPROPERTY(EditAnywhere)
    UDataTable* VehicleTruckBodyDT = nullptr;

    UPROPERTY(EditAnywhere)
    UDataTable* ItemDT = nullptr;

    UPROPERTY(EditAnywhere)
    UDataTable* WeaponDT = nullptr;
};
