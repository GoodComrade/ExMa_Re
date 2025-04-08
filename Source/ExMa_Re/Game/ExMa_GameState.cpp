// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/ExMa_GameState.h"
#include "GameFramework/Actor.h"
#include "ExMa_Re/Items/ItemObject.h"
#include "ExMa_Re/Items/ChestActor.h"
#include "Kismet/KismetSystemLibrary.h" 
#include "Engine/CollisionProfile.h"
#include "ExMa_Re/Components/InventoryComponent.h"
#include "ExMa_Re/Components/StructuralComponent.h"

#include "ExMa_Re/ConfigStruct/ItemConfigStruct.h"
#include "ExMa_Re/ConfigStruct/WeaponConfigStruct.h"
#include "ExMa_Re/ConfigStruct/VehicleConfigs/VehicleConfigStruct.h"

#include "ExMa_Re/Items/WeaponItemObject.h"

#include "ExMa_Re/DataAssets/ItemDataAsset.h"
#include "ExMa_Re/DataAssets/WeaponDataAsset.h"

#include "ExMa_Re/Vehicles/ExMa_RePawn.h"
#include "ExMa_Re/Vehicles/VehicleParts/VehiclePart.h"

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

void AExMa_GameState::SpawnCarPawn(FVehicleConfigStruct TargetVehicleConfigRow, FCarBodyConfigStruct TargetCarBodyConfigRow)
{
	auto VehicleData = TargetVehicleConfigRow.VehicleData;

	if (VehicleData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: VehicleData is NULLPTR!"));
		return;
	}

	VehicleData->VehicleType = TargetVehicleConfigRow.VehicleType;
	VehicleData->Health = TargetVehicleConfigRow.MaxHealth;
	VehicleData->MaxHealth = TargetVehicleConfigRow.MaxHealth;
	VehicleData->Armor = TargetVehicleConfigRow.MaxArmor;
	VehicleData->MaxArmor = TargetVehicleConfigRow.MaxArmor;
	VehicleData->Weight = TargetVehicleConfigRow.Weight;
	VehicleData->MaxWeight = TargetVehicleConfigRow.MaxWeight;
	VehicleData->BulletResistance = TargetVehicleConfigRow.BulletResistance;
	VehicleData->ExplosionResistance = TargetVehicleConfigRow.ExplosionResistance;
	VehicleData->EnergyResistance = TargetVehicleConfigRow.EnergyResistance;

	auto CarBodyData = TargetCarBodyConfigRow.CarBodyData;

	if (CarBodyData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: CarBodyData is NULLPTR!"));
		return;
	}

	CarBodyData->Health = TargetCarBodyConfigRow.MaxHealth;
	CarBodyData->MaxHealth = TargetCarBodyConfigRow.MaxHealth;
	CarBodyData->Armor = TargetCarBodyConfigRow.MaxArmor;
	CarBodyData->MaxArmor = TargetCarBodyConfigRow.MaxArmor;

	CarBodyData->GasTankSize = TargetCarBodyConfigRow.GasTankSize;
	CarBodyData->TrunkSize = TargetCarBodyConfigRow.TrunkSize;

	CarBodyData->MaxTorque = TargetCarBodyConfigRow.MaxTorque;
	CarBodyData->MaxRPM = TargetCarBodyConfigRow.MaxRPM;
	CarBodyData->EngineIdleRPM = TargetCarBodyConfigRow.EngineIdleRPM;
	CarBodyData->EngineBrakeEffect = TargetCarBodyConfigRow.EngineBrakeEffect;
	CarBodyData->EngineRPMSpeedup = TargetCarBodyConfigRow.EngineRPMSpeedup;
	CarBodyData->EngineRPMSlowdown = TargetCarBodyConfigRow.EngineRPMSlowdown;
	
	CarBodyData->ChassisHeight = TargetCarBodyConfigRow.ChassisHeight;
	CarBodyData->DragCoefficient = TargetCarBodyConfigRow.DragCoefficient;
	CarBodyData->DownforceCoefficient = TargetCarBodyConfigRow.DownforceCoefficient;

	CarBodyData->TopSpeed = TargetCarBodyConfigRow.TopSpeed;
	CarBodyData->EnginePower = TargetCarBodyConfigRow.EnginePower;
	CarBodyData->VehicleUpgradeSlots = TargetCarBodyConfigRow.VehicleUpgradeSlots;
	CarBodyData->VehicleReinforceSlots = TargetCarBodyConfigRow.VehicleReinforceSlots;
	CarBodyData->WeaponSlots = TargetCarBodyConfigRow.WeaponSlots;

	auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PlayerController == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: PlayerController is NULLPTR!"));
		return;
	}

	//Start spawn config vehicle
	if (UWorld* World = GetWorld())
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		TSubclassOf<AExMa_RePawn> PawnClassToSpawn = VehicleData->GetPawnClass();
		if (PawnClassToSpawn == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: PawnClassToSpawn is NULLPTR!"));
			return;
		}

		AExMa_RePawn* PossessedPawn = Cast<AExMa_RePawn>(PlayerController->GetPawn());
		if (PossessedPawn == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: PossessedPawn is NULLPTR!"));
			return;
		}

		FVector PlayerPawnLocation = PossessedPawn->GetActorLocation();

		AExMa_RePawn* NewPlayerPawn = World->SpawnActor<AExMa_RePawn>(PawnClassToSpawn, PlayerPawnLocation, FRotator(), SpawnParams);
		if (NewPlayerPawn == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: NewPlayerPawn ISN'T CREATED!"));
			return;
		}

		NewPlayerPawn->SetVehicleData(VehicleData);
		NewPlayerPawn->SetupBaseVehicleAttributes();

		PlayerController->UnPossess();
		PossessedPawn->Destroy();

		PlayerController->Possess(NewPlayerPawn);

		//start spawn & apply car body
		TSubclassOf<AVehiclePart> VehiclePartToSpawn = CarBodyData->GetVehiclePartClass();
		if (PawnClassToSpawn == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: PawnClassToSpawn is NULLPTR!"));
			return;
		}

		FActorSpawnParameters CarBodySpawnParams;
		CarBodySpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		CarBodySpawnParams.Owner = NewPlayerPawn;
		AVehiclePart* NewCarBody = World->SpawnActor<AVehiclePart>(VehiclePartToSpawn, PlayerPawnLocation, FRotator(), CarBodySpawnParams);

		if (NewCarBody == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: NewCarBody ISN'T CREATED!"));
			return;
		}

		NewCarBody->SetVehiclePartData(CarBodyData);
		NewCarBody->SetVehiclePartMesh(CarBodyData->VehiclePartMesh);

		NewPlayerPawn->SetVehicleBody(NewCarBody);
	}
}

void AExMa_GameState::SpawnBaseTruckPawn(FVehicleConfigStruct TargetVehicleConfigRow, FTruckCabinConfigStruct TargetTruckCabinConfigRow)
{
}

void AExMa_GameState::SpawnTruckPawn(FVehicleConfigStruct TargetVehicleConfigRow, FTruckCabinConfigStruct TargetTruckCabinConfigRow, FTruckBodyConfigStruct TargetTruckBodyConfigRow)
{
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

