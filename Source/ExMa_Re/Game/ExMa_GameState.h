// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "ExMa_GameState.generated.h"

class UItemObject;
class AActor;
class AItemActor;
class UInventoryComponent;

UCLASS()
class EXMA_RE_API AExMa_GameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SpawnCrateActorFromPawn(TSubclassOf<AItemActor> ItemActorToSpawn, UInventoryComponent* InventoryToCopy, AActor* ActorFromSpawn, bool GroundClamp);

	UFUNCTION(BlueprintCallable)
	void SetGamePause(bool bIsPause);
};
