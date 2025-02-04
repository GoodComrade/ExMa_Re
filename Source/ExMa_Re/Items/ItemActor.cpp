// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ExMa_Re/Items/ItemObject.h"
#include "ExMa_Re/Vehicles/ExMa_RePawn.h"
#include "ExMa_Re/ConfigStruct/ItemConfigStruct.h"

// Sets default values
AItemActor::AItemActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ActorMesh"));
	ActorMesh->SetupAttachment(RootComponent);

	CollectSphere = CreateDefaultSubobject<USphereComponent>(TEXT("CollectSphere"));
	CollectSphere->SetupAttachment(ActorMesh);

	CollectSphere->OnComponentBeginOverlap.AddDynamic(this, &AItemActor::AItemActor::OnCollectSphereBeginOverlap);
}

void AItemActor::SetItemObject(UItemObject* ItemObjectToSet)
{
	ItemObject = ItemObjectToSet;
}

// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();

	if (ItemObject->IsValidLowLevel() == false)
		ItemObject = GetDefaultItemObject();
	
}

UItemObject* AItemActor::GetDefaultItemObject()
{
	FItemConfigStruct ConfigStruct;
	if (const FItemConfigStruct* ConfigStructRow = ItemsDataTable->FindRow<FItemConfigStruct>(ItemConfigRowName, ""))
		ConfigStruct = *ConfigStructRow;

	UItemObject* DefaultItem = NewObject<UItemObject>(UItemObject::StaticClass());

	if (DefaultItem == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("DEFAULT ITEM ISN'T CREATED!"));
		return nullptr;
	}

	DefaultItem->SetDimentions(ConfigStruct.SizeX, ConfigStruct.SizeY);
	DefaultItem->SetIcons(ConfigStruct.Icon, ConfigStruct.IconRotated);

	return DefaultItem;
}

void AItemActor::OnCollectSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (AExMa_RePawn* PlayerPawn = Cast<AExMa_RePawn>(OtherActor))
	{
		if (PlayerPawn->GetInventoryComponent()->TryAddItem(ItemObject))
			Destroy();
	}
}

void AItemActor::OnCollectSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

// Called every frame
void AItemActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

