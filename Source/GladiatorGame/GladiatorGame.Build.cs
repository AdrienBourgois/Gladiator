// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class GladiatorGame : ModuleRules
{
	public GladiatorGame(TargetInfo Target)
	{
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "AIModule", "UMG", "Slate", "SlateCore", "OnlineSubsystem", "OnlineSubsystemUtils" });

        PrivateDependencyModuleNames.AddRange(new string[] { "AIModule", "GameplayTasks", "OnlineSubsystem", "OnlineSubsystemNull" });

        //DynamicallyLoadedModuleNames.Add("OnlineSubsystemNull");

    }
}
