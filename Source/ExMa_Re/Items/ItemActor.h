// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ExMa_Re/ConfigStruct/ItemConfigStruct.h"
#include "ItemActor.generated.h"

class UItemObject;

UCLASS()
class EXMA_RE_API AItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemActor();

	UFUNCTION()
	void SetItemObject(UItemObject* ItemObjectToSet);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual UItemObject* GetDefaultItemObject();

	//TODO: show player pickup dialogue with hotkey instead of straigth pickup
	UFUNCTION()
	void OnCollectSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnCollectSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ActorMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USphereComponent* CollectSphere;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true", InstanceEditable = "true"))
	UItemObject* ItemObject;

	//TODO: Implement logic of populationg this array
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true", InstanceEditable = "true"))
	TArray<UItemObject*> StoredItems;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true", InstanceEditable = "true"))
	FName ItemConfigRowName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true", ExposeOnSpawn = "true", InstanceEditable = "true"))
	UDataTable* ItemsDataTable;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
