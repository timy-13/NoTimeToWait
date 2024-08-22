// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class NoTimeToWait : ModuleRules
{
	public NoTimeToWait(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "GameplayTags" });
	}
}