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
#include "ExMa_Re/Items/WeaponActor.h"

#include "ExMa_Re/DataAssets/ItemDataAsset.h"
#include "ExMa_Re/DataAssets/WeaponDataAsset.h"

#include "ExMa_Re/DataAssets/Vehicles/VehicleDataAsset.h"
#include "ExMa_Re/DataAssets/Vehicles/VehicleParts/VehiclePartDataAsset.h"
#include "ExMa_Re/DataAssets/Vehicles/VehicleParts/Car/CarBodyDataAsset.h"
#include "ExMa_Re/DataAssets/Vehicles/VehicleParts/Truck/TruckCabinDataAsset.h"
#include "ExMa_Re/DataAssets/Vehicles/VehicleParts/Truck/TruckBodyDataAsset.h"

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

	if (ConfigStruct.ItemData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: ConfigStruct.ItemData is nullptr"));
		return nullptr;
	}

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
	//WeaponItem->SetItemData(WeaponDataAsset);
	return WeaponItem;
}

void AExMa_GameState::SpawnCarPawn(FVehicleConfigStruct TargetVehicleConfigRow, FCarBodyConfigStruct TargetCarBodyConfigRow)
{
	//Init Vehicle DataAsset
	UVehicleDataAsset* VehicleData = MakeVehicleDataAsset(TargetVehicleConfigRow);
	if (VehicleData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: VehicleData is NULLPTR!"));
		return;
	}

	//GetPlayerController & PossessedPawn
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: PlayerController is NULLPTR!"));
		return;
	}

	AExMa_RePawn* PossessedPawn = Cast<AExMa_RePawn>(PlayerController->GetPawn());
	if (PossessedPawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: Possessed Pawn is NULLPTR!"));
		return;
	}

	FVector PlayerPawnLocation = PossessedPawn->GetActorLocation();

	//Init CarBodyDataAsset
	UCarBodyDataAsset* CarBodyData = MakeCarBodyDataAsset(TargetCarBodyConfigRow);
	if (CarBodyData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: CarBodyData is NULLPTR!"));
		return;
	}

	//Start spawn config vehicle
	if (UWorld* World = GetWorld())
	{
		AExMa_RePawn* NewPlayerPawn = CreateAndPossessVehicle(VehicleData, PlayerController, PossessedPawn, PlayerPawnLocation, World);
		if (NewPlayerPawn == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: NewPlayerPawn ISN'T CREATED!"));
			return;
		}

		//start spawn & apply car body
		AVehiclePart* NewCarBody = CreateVehiclePart(CarBodyData, NewPlayerPawn, PlayerPawnLocation, World);
		if (NewCarBody == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: NewCarBody ISN'T CREATED!"));
			return;
		}

		//NewCarBody->SetVehiclePartData(CarBodyData);

		NewPlayerPawn->SetVehicleBody(NewCarBody);
	}
}

void AExMa_GameState::SpawnTruckPawn(FVehicleConfigStruct TargetVehicleConfigRow, FTruckCabinConfigStruct TargetTruckCabinConfigRow, FTruckBodyConfigStruct TargetTruckBodyConfigRow)
{
	//Init Vehicle DataAsset
	UVehicleDataAsset* VehicleData = MakeVehicleDataAsset(TargetVehicleConfigRow);
	if (VehicleData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: VehicleData is NULLPTR!"));
		return;
	}

	//GetPlayerController & PossessedPawn
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (PlayerController == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: PlayerController is NULLPTR!"));
		return;
	}

	AExMa_RePawn* PossessedPawn = Cast<AExMa_RePawn>(PlayerController->GetPawn());
	if (PossessedPawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: PossessedPawn is NULLPTR!"));
		return;
	}

	FVector PlayerPawnLocation = PossessedPawn->GetActorLocation();

	//Init Cabin DataAsset
	UTruckCabinDataAsset* TruckCabinData = MakeTruckCabinDataAsset(TargetTruckCabinConfigRow);
	if (TruckCabinData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: TruckCabinData is NULLPTR!"));
		return;
	}

	//Init Body DataAsset
	UTruckBodyDataAsset* TruckBodyData = MakeTruckBodyDataAsset(TargetTruckBodyConfigRow);
	if (TruckBodyData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: CarBodyData is NULLPTR!"));
		return;
	}

	//Start spawn config vehicle
	if (UWorld* World = GetWorld())
	{
		AExMa_RePawn* NewPlayerPawn = CreateAndPossessVehicle(VehicleData, PlayerController, PossessedPawn, PlayerPawnLocation, World);
		if (NewPlayerPawn == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: NewPlayerPawn ISN'T CREATED!"));
			return;
		}

		//start spawn & apply Truck cabin
		AVehiclePart* NewTruckCabin = CreateVehiclePart(TruckCabinData, NewPlayerPawn, PlayerPawnLocation, World);
		if (NewTruckCabin == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: NewTruckCabin ISN'T CREATED!"));
			return;
		}

		//NewTruckCabin->SetVehiclePartData(TruckCabinData);
		
		//start spawn & apply Truck body
		AVehiclePart* NewTruckBody = CreateVehiclePart(TruckBodyData, NewPlayerPawn, PlayerPawnLocation, World);
		if (NewTruckCabin == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: NewTruckCabin ISN'T CREATED!"));
			return;
		}

		//NewTruckBody->SetVehiclePartData(TruckBodyData);
		NewPlayerPawn->SetVehicleCabin(NewTruckCabin);
		NewPlayerPawn->SetVehicleBody(NewTruckBody);
	}
}

AWeaponActor* AExMa_GameState::SpawnWeaponActor(AActor* TargetOwner, FName TargetSlotSocket)
{
	AExMa_RePawn* TargetOwnerPawn = Cast<AExMa_RePawn>(TargetOwner);
	if (!TargetOwner)
	{
		UE_LOG(LogTemp, Error, TEXT("AExMa_GameState::SpawnWeaponActor: TargetOwnerActor is NULLPTR!"));
		return nullptr;
	}

	if (UWorld* World = GetWorld())
	{
		FActorSpawnParameters WeaponSpawnParams;
		WeaponSpawnParams.Owner = TargetOwnerPawn;
		WeaponSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		AWeaponActor* NewWeapon = World->SpawnActor<AWeaponActor>(AWeaponActor::StaticClass(), TargetOwnerPawn->GetActorLocation(), FRotator(), WeaponSpawnParams);
		if (!NewWeapon)
		{
			UE_LOG(LogTemp, Error, TEXT("AExMa_GameState::SpawnWeaponActor: NewWeapon is NULLPTR!"));
			return nullptr;
		}

		AVehiclePart* TargetVehiclePart = TargetOwnerPawn->GetStructuralComponent()->GetTargetVehiclePartBySocket(TargetSlotSocket);
		if (!TargetVehiclePart)
		{
			UE_LOG(LogTemp, Error, TEXT("AExMa_GameState::SpawnWeaponActor: TargetVehiclePart is NULLPTR!"));
			return nullptr;
		}

		NewWeapon->AttachToComponent(TargetVehiclePart->GetVehicleStaticMeshComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, TargetSlotSocket);

		return NewWeapon;
	}

	return nullptr;
}

void AExMa_GameState::SpawnCarNPC(FVehicleConfigStruct TargetVehicleConfigRow, 
								  FCarBodyConfigStruct TargetCarBodyConfigRow, 
								  FName TargetWeaponName,
								  UDataTable* ItemsDT,
								  UDataTable* WeaponsDT,
								  FVector SpawnLocation)
{
	//Init Vehicle DataAsset
	UVehicleDataAsset* VehicleData = MakeVehicleDataAsset(TargetVehicleConfigRow);
	if (VehicleData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: VehicleData is NULLPTR!"));
		return;
	}

	//Init CarBodyDataAsset
	UCarBodyDataAsset* CarBodyData = MakeCarBodyDataAsset(TargetCarBodyConfigRow);
	if (CarBodyData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: CarBodyData is NULLPTR!"));
		return;
	}

	//Start spawn config vehicle
	if (UWorld* World = GetWorld())
	{
		AExMa_RePawn* NewPlayerPawn = CreateVehicleNPC(VehicleData, SpawnLocation, World);
		if (NewPlayerPawn == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: NewPlayerPawn ISN'T CREATED!"));
			return;
		}

		//start spawn & apply car body
		AVehiclePart* NewCarBody = CreateVehiclePart(CarBodyData, NewPlayerPawn, SpawnLocation, World);
		if (NewCarBody == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: NewCarBody ISN'T CREATED!"));
			return;
		}

		//NewCarBody->SetVehiclePartData(CarBodyData);

		NewPlayerPawn->SetVehicleBody(NewCarBody);

		UItemObject* NewItem = CreateItem(TargetWeaponName, ItemsDT, WeaponsDT);
		UWeaponItemObject* NewWeapon = Cast<UWeaponItemObject>(NewItem);

		if (NewWeapon)
			NewPlayerPawn->GetWeaponComponent()->GetSlotByIndex(0)->AddWeaponInSlot(NewWeapon);
	}
}

void AExMa_GameState::SpawnTruckNPC(FVehicleConfigStruct TargetVehicleConfigRow, 
									FTruckCabinConfigStruct TargetTruckCabinConfigRow, 
									FTruckBodyConfigStruct TargetTruckBodyConfigRow, 
									FName TargetWeaponName,
									UDataTable* ItemsDT,
									UDataTable* WeaponsDT,
									FVector SpawnLocation)
{
	//Init Vehicle DataAsset
	UVehicleDataAsset* VehicleData = MakeVehicleDataAsset(TargetVehicleConfigRow);
	if (VehicleData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: VehicleData is NULLPTR!"));
		return;
	}

	//Init Cabin DataAsset
	UTruckCabinDataAsset* TruckCabinData = MakeTruckCabinDataAsset(TargetTruckCabinConfigRow);
	if (TruckCabinData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: TruckCabinData is NULLPTR!"));
		return;
	}

	//Init Body DataAsset
	UTruckBodyDataAsset* TruckBodyData = MakeTruckBodyDataAsset(TargetTruckBodyConfigRow);
	if (TruckBodyData == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: CarBodyData is NULLPTR!"));
		return;
	}

	//Start spawn config vehicle
	if (UWorld* World = GetWorld())
	{
		AExMa_RePawn* NewPlayerPawn = CreateVehicleNPC(VehicleData, SpawnLocation, World);
		if (NewPlayerPawn == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: NewPlayerPawn ISN'T CREATED!"));
			return;
		}

		//start spawn & apply Truck cabin
		AVehiclePart* NewTruckCabin = CreateVehiclePart(TruckCabinData, NewPlayerPawn, SpawnLocation, World);
		if (NewTruckCabin == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: NewTruckCabin ISN'T CREATED!"));
			return;
		}

		//NewTruckCabin->SetVehiclePartData(TruckCabinData);

		//start spawn & apply Truck body
		AVehiclePart* NewTruckBody = CreateVehiclePart(TruckBodyData, NewPlayerPawn, SpawnLocation, World);
		if (NewTruckCabin == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("AExMa_GameState:: NewTruckCabin ISN'T CREATED!"));
			return;
		}

		//NewTruckBody->SetVehiclePartData(TruckBodyData);
		NewPlayerPawn->SetVehicleCabin(NewTruckCabin);
		NewPlayerPawn->SetVehicleBody(NewTruckBody);

		UItemObject* NewItem = CreateItem(TargetWeaponName, ItemsDT, WeaponsDT);
		UWeaponItemObject* NewWeapon = Cast<UWeaponItemObject>(NewItem);

		if(NewWeapon)
			NewPlayerPawn->GetWeaponComponent()->GetSlotByIndex(0)->AddWeaponInSlot(NewWeapon);
	}
}

AExMa_RePawn* AExMa_GameState::CreateVehicleNPC(UVehicleDataAsset* VehicleData, FVector SpawnLocation, UWorld* World)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	TSubclassOf<AExMa_RePawn> PawnClassToSpawn = VehicleData->GetPawnClass();
	if (PawnClassToSpawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AExMa_GameState::CreateAndPossessVehicle: PawnClassToSpawn is NULLPTR!"));
		return nullptr;
	}

	AExMa_RePawn* NewPlayerPawn = World->SpawnActor<AExMa_RePawn>(PawnClassToSpawn, SpawnLocation, FRotator(), SpawnParams);
	if (NewPlayerPawn == nullptr)
		return nullptr;

	NewPlayerPawn->SetVehicleData(VehicleData);
	NewPlayerPawn->SetupBaseVehicleAttributes();

	return NewPlayerPawn;
}

UVehicleDataAsset* AExMa_GameState::MakeVehicleDataAsset(FVehicleConfigStruct TargetVehicleConfigRow)
{
	UVehicleDataAsset* VehicleData = TargetVehicleConfigRow.VehicleData;

	if (VehicleData == nullptr)
		return nullptr;

	VehicleData->VehicleType = TargetVehicleConfigRow.VehicleType;

	VehicleData->Health = TargetVehicleConfigRow.MaxHealth;
	VehicleData->MaxHealth = TargetVehicleConfigRow.MaxHealth;

	VehicleData->Armor = TargetVehicleConfigRow.MaxArmor;
	VehicleData->MaxArmor = TargetVehicleConfigRow.MaxArmor;

	VehicleData->Weight = TargetVehicleConfigRow.Weight;
	VehicleData->MaxWeight = TargetVehicleConfigRow.MaxWeight;

	VehicleData->Cost = TargetVehicleConfigRow.Cost;

	VehicleData->BulletResistance = TargetVehicleConfigRow.BulletResistance;
	VehicleData->ExplosionResistance = TargetVehicleConfigRow.ExplosionResistance;
	VehicleData->EnergyResistance = TargetVehicleConfigRow.EnergyResistance;

	return VehicleData;
}

UCarBodyDataAsset* AExMa_GameState::MakeCarBodyDataAsset(FCarBodyConfigStruct TargetCarBodyConfigRow)
{
	UCarBodyDataAsset* CarBodyData = TargetCarBodyConfigRow.CarBodyData;

	if (CarBodyData == nullptr)
		return nullptr;

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

	CarBodyData->BulletResistance = TargetCarBodyConfigRow.BulletResistance;
	CarBodyData->ExplosionResistance = TargetCarBodyConfigRow.ExplosionResistance;
	CarBodyData->EnergyResistance = TargetCarBodyConfigRow.EnergyResistance;

	CarBodyData->Weight = TargetCarBodyConfigRow.Weight;
	CarBodyData->Cost = TargetCarBodyConfigRow.Cost;

	return CarBodyData;
}

UTruckCabinDataAsset* AExMa_GameState::MakeTruckCabinDataAsset(FTruckCabinConfigStruct TargetTruckCabinConfigRow)
{
	UTruckCabinDataAsset* TruckCabinData = TargetTruckCabinConfigRow.TruckCabinData;

	if (TruckCabinData == nullptr)
		return nullptr;

	TruckCabinData->Health = TargetTruckCabinConfigRow.MaxHealth;
	TruckCabinData->MaxHealth = TargetTruckCabinConfigRow.MaxHealth;

	TruckCabinData->Armor = TargetTruckCabinConfigRow.MaxArmor;
	TruckCabinData->MaxArmor = TargetTruckCabinConfigRow.MaxArmor;

	TruckCabinData->GasTankSize = TargetTruckCabinConfigRow.GasTankSize;

	TruckCabinData->MaxTorque = TargetTruckCabinConfigRow.MaxTorque;
	TruckCabinData->MaxRPM = TargetTruckCabinConfigRow.MaxRPM;
	TruckCabinData->EngineIdleRPM = TargetTruckCabinConfigRow.EngineIdleRPM;
	TruckCabinData->EngineBrakeEffect = TargetTruckCabinConfigRow.EngineBrakeEffect;
	TruckCabinData->EngineRPMSpeedup = TargetTruckCabinConfigRow.EngineRPMSpeedup;
	TruckCabinData->EngineRPMSlowdown = TargetTruckCabinConfigRow.EngineRPMSlowdown;

	TruckCabinData->ChassisHeight = TargetTruckCabinConfigRow.ChassisHeight;
	TruckCabinData->DragCoefficient = TargetTruckCabinConfigRow.DragCoefficient;
	TruckCabinData->DownforceCoefficient = TargetTruckCabinConfigRow.DownforceCoefficient;

	TruckCabinData->TopSpeed = TargetTruckCabinConfigRow.TopSpeed;
	TruckCabinData->EnginePower = TargetTruckCabinConfigRow.EnginePower;

	TruckCabinData->VehicleUpgradeSlots = TargetTruckCabinConfigRow.VehicleUpgradeSlots;
	TruckCabinData->VehicleReinforceSlots = TargetTruckCabinConfigRow.VehicleReinforceSlots;

	TruckCabinData->Weight = TargetTruckCabinConfigRow.Weight;
	TruckCabinData->Cost = TargetTruckCabinConfigRow.Cost;

	TruckCabinData->BulletResistance = TargetTruckCabinConfigRow.BulletResistance;
	TruckCabinData->ExplosionResistance = TargetTruckCabinConfigRow.ExplosionResistance;
	TruckCabinData->EnergyResistance = TargetTruckCabinConfigRow.EnergyResistance;

	return TruckCabinData;
}

UTruckBodyDataAsset* AExMa_GameState::MakeTruckBodyDataAsset(FTruckBodyConfigStruct TargetTruckBodyConfigRow)
{
	UTruckBodyDataAsset* TruckBodyData = TargetTruckBodyConfigRow.TruckBodyData;

	if (TruckBodyData == nullptr)
		return nullptr;

	TruckBodyData->Health = TargetTruckBodyConfigRow.MaxHealth;
	TruckBodyData->MaxHealth = TargetTruckBodyConfigRow.MaxHealth;

	TruckBodyData->Armor = TargetTruckBodyConfigRow.MaxArmor;
	TruckBodyData->MaxArmor = TargetTruckBodyConfigRow.MaxArmor;

	TruckBodyData->TrunkSize = TargetTruckBodyConfigRow.TrunkSize;

	TruckBodyData->Weight = TargetTruckBodyConfigRow.Weight;
	TruckBodyData->Cost = TargetTruckBodyConfigRow.Cost;

	TruckBodyData->BulletResistance = TargetTruckBodyConfigRow.BulletResistance;
	TruckBodyData->ExplosionResistance = TargetTruckBodyConfigRow.ExplosionResistance;
	TruckBodyData->EnergyResistance = TargetTruckBodyConfigRow.EnergyResistance;

	return TruckBodyData;
}

AExMa_RePawn* AExMa_GameState::CreateAndPossessVehicle(UVehicleDataAsset* VehicleData, APlayerController* PlayerController, AExMa_RePawn* PossessedPawn, FVector PlayerPawnLocation, UWorld* World)
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	SpawnParams.Owner = PlayerController;

	TSubclassOf<AExMa_RePawn> PawnClassToSpawn = VehicleData->GetPawnClass();
	if (PawnClassToSpawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AExMa_GameState::CreateAndPossessVehicle: PawnClassToSpawn is NULLPTR!"));
		return nullptr;
	}

	AExMa_RePawn* NewPlayerPawn = World->SpawnActor<AExMa_RePawn>(PawnClassToSpawn, PlayerPawnLocation, FRotator(), SpawnParams);
	if (NewPlayerPawn == nullptr)
		return nullptr;

	NewPlayerPawn->SetVehicleData(VehicleData);
	NewPlayerPawn->SetupBaseVehicleAttributes();

	PlayerController->UnPossess();
	PossessedPawn->GetStructuralComponent()->DestroyCabin();
	PossessedPawn->GetStructuralComponent()->DestroyBody();
	PossessedPawn->GetWeaponComponent()->DestroyWeaponSlots();
	PossessedPawn->Destroy();

	PlayerController->Possess(NewPlayerPawn);

	return NewPlayerPawn;
}

AVehiclePart* AExMa_GameState::CreateVehiclePart(UVehiclePartDataAsset* TargetData, AExMa_RePawn* OwnerPawn, FVector PlayerPawnLocation, UWorld* World)
{
	TSubclassOf<AVehiclePart> VehiclePartToSpawn = TargetData->GetVehiclePartClass();
	if (VehiclePartToSpawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AExMa_GameState::CreateVehiclePart: VehiclePartToSpawn is NULLPTR!"));
		return nullptr;
	}

	FActorSpawnParameters CarBodySpawnParams;
	CarBodySpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	CarBodySpawnParams.Owner = OwnerPawn;

	AVehiclePart* NewVehiclePart = World->SpawnActor<AVehiclePart>(VehiclePartToSpawn, PlayerPawnLocation, FRotator(), CarBodySpawnParams);
	if (NewVehiclePart == nullptr)
		return nullptr;	

	NewVehiclePart->SetVehiclePartData(TargetData);
	//NewVehiclePart->SetVehiclePartMesh(TargetData->VehiclePartMesh);

	return NewVehiclePart;
}

