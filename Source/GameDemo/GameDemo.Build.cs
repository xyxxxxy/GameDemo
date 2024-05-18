// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GameDemo : ModuleRules
{
	public GameDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine",
			"InputCore","GameplayTags","PhysicsCore","Niagara","SlateCore"});
		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
	}
}
