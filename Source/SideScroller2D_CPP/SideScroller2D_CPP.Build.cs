// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SideScroller2D_CPP : ModuleRules
{
	public SideScroller2D_CPP(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
