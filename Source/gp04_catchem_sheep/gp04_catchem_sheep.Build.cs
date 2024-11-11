// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class gp04_catchem_sheep : ModuleRules
{
	public gp04_catchem_sheep(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[]
		{
			
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"GameplayTags",
			"EnhancedInput",
			"UMG",
			"AIModule",
            "Niagara",
			"NavigationSystem",
			"FMODStudio"
        });

		if (Target.Type == TargetType.Editor)
		{
		    PublicDependencyModuleNames.AddRange(new string[] { "UnrealEd" });
		}

		PrivateDependencyModuleNames.AddRange(new string[] {  });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
