// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "VehiclePart.generated.h"

class UVehiclePartDataAsset;

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
	void SetVehiclePartData(UVehiclePartDataAsset* DataToSet);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn))
	UVehiclePartDataAsset* VehiclePartData;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
