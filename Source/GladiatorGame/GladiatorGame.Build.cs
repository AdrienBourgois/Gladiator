// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class GladiatorGame : ModuleRules
{
	public GladiatorGame(TargetInfo Target)
	{
        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "AIModule", "UMG", "Slate", "SlateCore"/*, "OnlineSubsystem", "OnlineSubsystemUtils", "OnlineSubsystemNull" */});

        PrivateDependencyModuleNames.AddRange(new string[] { "AIModule", "GameplayTasks"/*, "OnlineSubsystem", "OnlineSubsystemNull"*/ });

        //if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64))
        //{
        //    DynamicallyLoadedModuleNames.Add("OnlineSubsystemNull");
        //    //if (UEBuildConfiguration.bCompileSteamOSS == true)
        //    //{
        //    //    DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
        //    //}
        //}

    }
}
