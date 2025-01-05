// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ExMa_Re : ModuleRules
{
	public ExMa_Re(ReadOnlyTargetRules Target) : base(Target)
	{
        PrivateDependencyModuleNames.AddRange(new string[] {
            "Slate", "SlateCore"});

        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "ChaosVehicles", "PhysicsCore" , "UMG", "GameplayTasks",
            "GameplayAbilities", "AIModule", "GameplayTags"
        });

        PublicIncludePaths.Add("ExMa_Re");
    }
}
