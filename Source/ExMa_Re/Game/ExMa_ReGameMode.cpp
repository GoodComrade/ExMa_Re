// Copyright Epic Games, Inc. All Rights Reserved.

#include "ExMa_ReGameMode.h"
#include "ExMa_RePlayerController.h"

AExMa_ReGameMode::AExMa_ReGameMode()
{
	PlayerControllerClass = AExMa_RePlayerController::StaticClass();
}
