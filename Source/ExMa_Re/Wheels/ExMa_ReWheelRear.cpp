// Copyright Epic Games, Inc. All Rights Reserved.

#include "ExMa_ReWheelRear.h"
#include "UObject/ConstructorHelpers.h"

UExMa_ReWheelRear::UExMa_ReWheelRear()
{
	AxleType = EAxleType::Rear;
	bAffectedByHandbrake = true;
	bAffectedByEngine = true;
}