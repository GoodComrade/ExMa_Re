// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/ExMa_GameState.h"
#include "GameFramework/Actor.h"
#include "ExMa_Re/Items/ItemObject.h"
#include "ExMa_Re/Items/ItemActor.h"
#include "Kismet/KismetSystemLibrary.h" 
#include "Engine/CollisionProfile.h"
#include "ExMa_Re/Components/InventoryComponent.h"
#include "Kismet/GameplayStatics.h"

//TODO: Change this logic to spawn one certain ItemActor with droppedItemObjects
void AExMa_GameState::SpawnCrateActorFromPawn(TSubclassOf<AItemActor> ItemActorToSpawn, UInventoryComponent* InventoryToCopy, AActor* ActorFromSpawn, bool GroundClamp)
{
	FVector SpawnLocation = ActorFromSpawn->GetActorLocation() + (ActorFromSpawn->GetActorRightVector() * 600.f);
	FVector LineTraceEndLocation = SpawnLocation - FVector(0, 0, 1000);
	ETraceTypeQuery TraceChannel = UEngineTypes::ConvertToTraceType(ECollisionChannel::ECC_Visibility);
	const TArray<AActor*> ActorsToIgnore;
	FHitResult HitResult;
	float DrawTime = 5.0f;

	if (GroundClamp)
	{
		if (UKismetSystemLibrary::LineTraceSingle(
			GetWorld(), 
			SpawnLocation, 
			LineTraceEndLocation, 
			TraceChannel, 
			false, 
			ActorsToIgnore, 
			EDrawDebugTrace::None, 
			HitResult, true, 
			FColor::Red, 
			FColor::Green, 
			DrawTime))
		{
			SpawnLocation = HitResult.Location;
		}
	}

	if (UWorld* World = GetWorld())
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
		AItemActor* ItemActor = World->SpawnActor<AItemActor>(ItemActorToSpawn, SpawnLocation + FVector(0, 250, 0), FRotator(), SpawnParams);
	
		if(ItemActor != nullptr)
			ItemActor->RecieveItemsWithOverride(InventoryToCopy);
	}
}

void AExMa_GameState::SetGamePause(bool bIsPause)
{
	UWorld* World = GetWorld();

	if (World == nullptr)
		return;

	UGameplayStatics::SetGamePaused(World, bIsPause);
}
