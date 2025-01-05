// Copyright Epic Games, Inc. All Rights Reserved.


#include "ExMa_ReUI.h"

void UExMa_ReUI::UpdateSpeed(float NewSpeed)
{
	// format the speed to KPH or MPH
	float FormattedSpeed = FMath::Abs(NewSpeed) * (bIsMPH ? 0.022f : 0.036f);

	// call the Blueprint handler
	OnSpeedUpdate(FormattedSpeed);
}

void UExMa_ReUI::UpdateGear(int32 NewGear)
{
	// call the Blueprint handler
	OnGearUpdate(NewGear);
}