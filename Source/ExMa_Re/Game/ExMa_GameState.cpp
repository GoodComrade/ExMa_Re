// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/ExMa_GameState.h"
#include "GameFramework/Actor.h"
#include "ExMa_Re/Items/ItemObject.h"
#include "ExMa_Re/Items/ItemActor.h"
#include "Kismet/KismetSystemLibrary.h" 
#include "Engine/CollisionProfile.h"


void AExMa_GameState::SpawnItemFromActor(UItemObject* ItemObjectToSpawn, AActor* ActorFromSpawn, bool GroundClamp)
{
	FVector SpawnLocation = ActorFromSpawn->GetActorLocation() + (ActorFromSpawn->GetActorForwardVector() * -1 * 1000.f);
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

		AItemActor* ItemActor = World->SpawnActor<AItemActor>(ItemObjectToSpawn->GetItemActorClass(), SpawnLocation, FRotator(), SpawnParams);

		if(ItemActor != nullptr)
			ItemActor->SetItemObject(ItemObjectToSpawn);
	}
}
