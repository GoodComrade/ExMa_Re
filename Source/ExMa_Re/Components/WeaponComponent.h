// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ExMa_Re/Structs/TileStruct.h"
#include "WeaponComponent.generated.h"

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
	UFUNCTION(BlueprintCallable)
	void AddWeaponSlots(TArray<FTileStruct> SlotsDimentions);


	UFUNCTION(BlueprintCallable)
	UWeaponSlot* GetSlotByIndex(int SlotIndex);

private:
	TArray<UWeaponSlot*> WeaponSlots;
};
