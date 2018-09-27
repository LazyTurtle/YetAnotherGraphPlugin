#include "YetOtherGraphAssets.h"
#include "Logger.h"

#define LOCTEXT_NAMESPACE "FYetOtherGraphAssetsModule"

void FYetOtherGraphAssetsModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	LLog("Module loaded.");
}

void FYetOtherGraphAssetsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	LLog("Module unloaded.");
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FYetOtherGraphAssetsModule, YetAnotherGraphPlugin)