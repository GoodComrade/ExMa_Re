// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ExMa_Re/Structs/TileStruct.h"
#include "Components/StaticMeshComponent.h"
#include "ExMa_Re/Structs/WeaponSlotInfo.h"
#include "WeaponComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWeaponSlotCreated, UWeaponSlot*, CreatedSlot);

class UWeaponSlot;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class EXMA_RE_API UWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UPROPERTY(BlueprintAssignable, Category = "Event Dispatchers")
	FOnWeaponSlotCreated OnWeaponSlotCreated;

	UFUNCTION(BlueprintCallable)
	void AddWeaponSlots(TArray<FWeaponSlotInfo> SlotsArray, UStaticMeshComponent* TargetMesh);

	UFUNCTION(BlueprintCallable)
	UWeaponSlot* GetSlotByIndex(int SlotIndex);

private:
	TArray<UWeaponSlot*> WeaponSlots;

private:
	UFUNCTION()
	FName GetSocketNameWithPrefix(UStaticMeshComponent* StaticMeshComponent, const FString& Prefix);
};
