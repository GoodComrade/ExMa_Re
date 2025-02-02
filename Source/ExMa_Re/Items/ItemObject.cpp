// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/ItemObject.h"
#include "ExMa_Re/Items/ItemActor.h"

void UItemObject::SetDimentions(int DimentionX, int DimentionY)
{
	Dimensions = FVector2D(DimentionX, DimentionY);
}

void UItemObject::SetIcons(UMaterialInterface* InIcon, UMaterialInterface* InIconRotated)
{
	Icon = InIcon;
	IconRotated = InIconRotated;
}

void UItemObject::SetItemActorClass(TSubclassOf<AItemActor> InItemActorClass)
{
	ItemActorClass = InItemActorClass;
}
