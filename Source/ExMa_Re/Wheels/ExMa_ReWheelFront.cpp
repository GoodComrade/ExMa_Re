// Copyright Epic Games, Inc. All Rights Reserved.

#include "ExMa_ReWheelFront.h"
#include "UObject/ConstructorHelpers.h"

UExMa_ReWheelFront::UExMa_ReWheelFront()
{
	AxleType = EAxleType::Front;
	bAffectedBySteering = true;
	MaxSteerAngle = 40.f;
}