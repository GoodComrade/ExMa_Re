// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ExMa_Re/Vehicles/VehicleParts/VehiclePart.h"
#include "Engine/Texture2D.h"
#include "StructuralComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXMA_RE_API UStructuralComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStructuralComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	AVehiclePart* GetTargetVehiclePartBySocket(FName SocketName);

	UFUNCTION()
	void SetVehicleCabin(AVehiclePart* CabinToSet);

	UFUNCTION()
	void SetVehicleBody(AVehiclePart* BodyToSet);

	UFUNCTION()
	AVehiclePart* GetCabin() { return VehicleCabin; };

	UFUNCTION()
	AVehiclePart* GetBody() { return VehicleBody; };

	UFUNCTION()
	void DestroyCabin();

	UFUNCTION()
	void DestroyBody();

	UFUNCTION()
	void ProcessDetachComponentsOnDeath(UTexture2D* InDeathTexture);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* ChassisMesh;
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	AVehiclePart* VehicleCabin;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	AVehiclePart* VehicleBody;


	FName CabinSocket;
	FName BodySocket;
};
