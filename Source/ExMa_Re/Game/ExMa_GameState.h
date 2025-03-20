// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ExMa_Re/Items/ItemObject.h"
#include "ExMa_Re/ConfigStruct/ItemConfigStruct.h"
#include "ExMa_Re/ConfigStruct/WeaponConfigStruct.h"
#include "ExMa_GameState.generated.h"

class UItemObject;
class UWeaponItemObject;
class AActor;
class AChestActor;
class UInventoryComponent;

UCLASS()
class EXMA_RE_API AExMa_GameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SpawnCrateActorFromPawn(TSubclassOf<AChestActor> ItemActorToSpawn, UInventoryComponent* InventoryToCopy, AActor* ActorFromSpawn, bool GroundClamp);

	UFUNCTION(BlueprintCallable)
	void SetGamePause(bool bIsPause);

	UFUNCTION(BlueprintCallable)
	UItemObject* CreateItem(FName TargetItemName, UDataTable* ItemsDT, UDataTable* WeaponsDT);

private:
	UWeaponItemObject* CreateWeaponItem(FItemConfigStruct TargetItemRow, FName TargetWeaponName, UDataTable* WeaponsDT);

};
