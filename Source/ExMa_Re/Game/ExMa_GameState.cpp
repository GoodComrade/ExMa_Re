// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/ExMa_GameState.h"
#include "GameFramework/Actor.h"
#include "ExMa_Re/Items/ItemObject.h"
#include "ExMa_Re/Items/ChestActor.h"
#include "Kismet/KismetSystemLibrary.h" 
#include "Engine/CollisionProfile.h"
#include "ExMa_Re/Components/InventoryComponent.h"
#include "ExMa_Re/ConfigStruct/ItemConfigStruct.h"
#include "ExMa_Re/ConfigStruct/WeaponConfigStruct.h"
#include "ExMa_Re/Items/WeaponItemObject.h"

#include "ExMa_Re/DataAssets/ItemDataAsset.h"
#include "ExMa_Re/DataAssets/WeaponDataAsset.h"

#include "Kismet/GameplayStatics.h"

//TODO: Change this logic to spawn one certain ItemActor with droppedItemObjects
void AExMa_GameState::SpawnCrateActorFromPawn(TSubclassOf<AChestActor> ChestActorToSpawn, UInventoryComponent* InventoryToCopy, AActor* ActorFromSpawn, bool GroundClamp)
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
	
		AChestActor* ChestActor = World->SpawnActor<AChestActor>(ChestActorToSpawn, SpawnLocation + FVector(0, 250, 0), FRotator(), SpawnParams);
	
		if(ChestActor != nullptr)
			ChestActor->RecieveItemsWithOverride(InventoryToCopy);
	}
}

void AExMa_GameState::SetGamePause(bool bIsPause)
{
	UWorld* World = GetWorld();

	if (World == nullptr)
		return;

	UGameplayStatics::SetGamePaused(World, bIsPause);
}

UItemObject* AExMa_GameState::CreateItem(FName TargetItemName, UDataTable* ItemsDT, UDataTable* WeaponsDT)
{
	if (ItemsDT == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: ItemsDataTable is nullptr"));
		return nullptr;
	}

	FItemConfigStruct ConfigStruct;
	if (const FItemConfigStruct* ConfigStructRow = ItemsDT->FindRow<FItemConfigStruct>(TargetItemName, ""))
		ConfigStruct = *ConfigStructRow;
	
	FGameplayTag WeaponTag = FGameplayTag::RequestGameplayTag("Item.Weapon");

	if (ConfigStruct.ItemType.HasTag(WeaponTag))
	{
		return CreateWeaponItem(ConfigStruct, TargetItemName, WeaponsDT);
	}

	UE_LOG(LogTemp, Warning, TEXT("AExMa_GameState:: CreatingItemObject %s"), *TargetItemName.ToString());

	UItemObject* NewItem = ConfigStruct.ItemData->ConstructItemInstance();
	//UItemObject* NewItem = NewObject<UItemObject>(UItemObject::StaticClass());

	if (NewItem == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: NewItem '%s' ITEM ISN'T CREATED!"), *TargetItemName.ToString());
		return nullptr;
	}

	NewItem->SetDimentions(ConfigStruct.SizeX, ConfigStruct.SizeY);
	NewItem->SetIcons(ConfigStruct.Icon, ConfigStruct.IconRotated);

	NewItem->GetItemData()->DisplayName = FText::FromString(TargetItemName.ToString());
	NewItem->GetItemData()->Description = FText::FromString(ConfigStruct.Description);

	//TODO: погуглить как сетать тэги в контейнер через код.
	NewItem->GetItemData()->ItemType = ConfigStruct.ItemType;
	
	NewItem->GetItemData()->Weight = ConfigStruct.Weight;
	NewItem->GetItemData()->Cost = ConfigStruct.Cost;

	NewItem->GetItemData()->PreviewMesh = ConfigStruct.PreviewMesh;

	return NewItem;
}

UWeaponItemObject* AExMa_GameState::CreateWeaponItem(FItemConfigStruct TargetItemRow, FName TargetWeaponName, UDataTable* WeaponsDT)
{
	if (WeaponsDT == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: WeaponsDataTable is nullptr"));
		return nullptr;
	}

	UE_LOG(LogTemp, Warning, TEXT("AExMa_GameState:: CreatingWeaponObject %s"), *TargetWeaponName.ToString());

	FWeaponConfigStruct WeaponConfigStruct;
	if (const FWeaponConfigStruct* ConfigStructRow = WeaponsDT->FindRow<FWeaponConfigStruct>(TargetWeaponName, ""))
		WeaponConfigStruct = *ConfigStructRow;

	if (WeaponConfigStruct.WeaponData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: WeaponData is nullptr"));
		return nullptr;
	}
	UItemObject* ItemPtr = WeaponConfigStruct.WeaponData->ConstructItemInstance();
	UWeaponItemObject* WeaponItem = Cast<UWeaponItemObject>(ItemPtr);

	if (WeaponItem == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: Fail to create WeaponObject %s"), *TargetWeaponName.ToString());
		return nullptr;
	}

	WeaponItem->SetDimentions(TargetItemRow.SizeX, TargetItemRow.SizeY);
	WeaponItem->SetIcons(TargetItemRow.Icon, TargetItemRow.IconRotated);

	UWeaponDataAsset* WeaponDataAsset = Cast<UWeaponDataAsset>(WeaponItem->GetItemData());
	if (WeaponDataAsset == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: Missing weapon data asset %s"), *TargetWeaponName.ToString());
		return nullptr;
	}

	WeaponDataAsset->DisplayName = FText::FromString(TargetWeaponName.ToString());
	WeaponDataAsset->Description = FText::FromString(TargetItemRow.Description);

	//TODO: погуглить как сетать тэги в контейнер через код.
	WeaponDataAsset->ItemType = TargetItemRow.ItemType;
	WeaponDataAsset->Weight = TargetItemRow.Weight;
	WeaponDataAsset->Cost = TargetItemRow.Cost;
	WeaponDataAsset->PreviewMesh = TargetItemRow.PreviewMesh;

	//TODO: Тут седать свойсвта дата ассет оружия, которые потом будут сетаться в атрибуты оружия при установке в подходящий слот.
	WeaponDataAsset->WeaponMesh = WeaponConfigStruct.WeaponMesh;
	WeaponDataAsset->MeshABP = WeaponConfigStruct.MeshABP;

	WeaponDataAsset->WeaponType = WeaponConfigStruct.WeaponType;

	WeaponDataAsset->Damage = WeaponConfigStruct.Damage;
	WeaponDataAsset->DamageType = WeaponConfigStruct.DamageType;

	WeaponDataAsset->AttackCost = WeaponConfigStruct.AttackCost;
	WeaponDataAsset->Cooldown = WeaponConfigStruct.Cooldown;
	WeaponDataAsset->ShootDelay = WeaponConfigStruct.ShootDelay;
	WeaponDataAsset->ReloadTime = WeaponConfigStruct.ReloadTime;
	WeaponDataAsset->Spread = WeaponConfigStruct.Spread;

	WeaponDataAsset->MaxBulletsCount = WeaponConfigStruct.MaxBulletsCount;
	WeaponDataAsset->CurrenMagazineCapacity = WeaponConfigStruct.MagazineSize;
	WeaponDataAsset->MaxMagazineCapacity = WeaponConfigStruct.MagazineSize;

	WeaponDataAsset->MinRange = WeaponConfigStruct.MinRange;
	WeaponDataAsset->MaxRange = WeaponConfigStruct.MaxRange;

	WeaponDataAsset->Health = WeaponConfigStruct.MaxHealth;
	WeaponDataAsset->MaxHealth = WeaponConfigStruct.MaxHealth;

	WeaponDataAsset->AimTime = WeaponConfigStruct.AimTime;

	//Возможно, избыточное действие. надо проверить, будет ли все корректно работать без него.
	WeaponItem->SetItemData(WeaponDataAsset);
	return WeaponItem;
}

