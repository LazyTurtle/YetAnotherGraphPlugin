using UnrealBuildTool;

public class YetAnotherGraphEditor : ModuleRules
{
	public YetAnotherGraphEditor(ReadOnlyTargetRules Target) : base(Target)
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
                "YetAnotherGraphEditor/Private",
                "YetAnotherGraphEditor/Private/Utility",
                "YetAnotherGraphEditor/Private/Toolkits",
                "YetAnotherGraphEditor/Private/AssetTypeActions",
                "YetAnotherGraphEditor/Private/EditorGraph",
                "YetAnotherGraphEditor/Private/EditorGraph/Factories",
                "YetAnotherGraphEditor/Private/EditorGraph/SchemaActions",
                "YetAnotherGraphEditor/Private/EditorGraph/EditorNodes",
                "YetAnotherGraphEditor/Private/EditorGraph/SlateWidgets",

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
                "YetOtherGraphAssets",
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
                "EditorStyle",
                "UnrealEd",
                "AssetTools",
                "GraphEditor",
                "ApplicationCore",
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
