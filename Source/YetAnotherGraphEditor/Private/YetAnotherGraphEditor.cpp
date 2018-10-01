#include "YetAnotherGraphEditor.h"
#include "ModuleManager.h"
#include "IAssetTools.h"
#include "AssetToolsModule.h"
#include "YetOtherAssetTypeActions.h"
#include "EditorLogger.h"
#include "YetAnotherNodeClassHelper.h"
#include "YANode.h"
#include "SimpleNode.h"


#define LOCTEXT_NAMESPACE "FYetAnotherGraphEditorModule"

void FYetAnotherGraphEditorModule::StartupModule()
{
	
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	TSharedRef<IAssetTypeActions> Actions = MakeShareable(new FYetOtherAssetTypeActions());
	AssetTools.RegisterAssetTypeActions(Actions);

	EDLLog("Module loaded");

}

void FYetAnotherGraphEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	EDLLog("Module unloaded");
	NodeHelper.Reset();
}

void FYetAnotherGraphEditorModule::StartNodeHelper()
{
	if (!NodeHelper.IsValid())
	{
		NodeHelper = MakeShareable(new FYetAnotherNodeClassHelper(UYANode::StaticClass()));
		FYetAnotherNodeClassHelper::AddObservedBlueprintClasses(USimpleNode::StaticClass());
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FYetAnotherGraphEditorModule, YetAnotherGraphPlugin)