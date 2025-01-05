// Copyright Epic Games, Inc. All Rights Reserved.


#include "ExMa_ReSportsWheelRear.h"

UExMa_ReSportsWheelRear::UExMa_ReSportsWheelRear()
{
	WheelRadius = 40.f;
	WheelWidth = 40.0f;
	FrictionForceMultiplier = 4.0f;
	SlipThreshold = 100.0f;
	SkidThreshold = 100.0f;
	MaxSteerAngle = 0.0f;
	MaxHandBrakeTorque = 6000.0f;
}