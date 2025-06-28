// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class T3_ARQ : ModuleRules
{
	public T3_ARQ(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Niagara"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"T3_ARQ",
			"T3_ARQ/Variant_Platforming",
			"T3_ARQ/Variant_Combat",
			"T3_ARQ/Variant_Combat/AI",
			"T3_ARQ/Variant_SideScrolling",
			"T3_ARQ/Variant_SideScrolling/Gameplay",
			"T3_ARQ/Variant_SideScrolling/AI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
