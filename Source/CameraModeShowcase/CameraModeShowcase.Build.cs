// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CameraModeShowcase : ModuleRules
{
	public CameraModeShowcase(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
