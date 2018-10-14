// Copyright (c) 2018 Jhonny Hueller
using UnrealBuildTool;

public class YetOtherGraphAssets : ModuleRules
{
	public YetOtherGraphAssets(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
				// ... add public include paths required here ...
            }
            );
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				// ... add other private include paths required here ...
                "YetOtherGraphAssets/Private",
                "YetOtherGraphAssets/Private/Graphs",
                "YetOtherGraphAssets/Private/Nodes",
                "YetOtherGraphAssets/Private/Utility",
            }
            );
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
                "Slate",
                "SlateCore",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
