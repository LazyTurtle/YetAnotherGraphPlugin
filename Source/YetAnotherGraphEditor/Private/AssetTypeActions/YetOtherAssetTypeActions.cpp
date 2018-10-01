#include "YetOtherAssetTypeActions.h"
#include "YAGraph.h"
#include "YetAnotherGraphEditorToolkit.h"
#include "ModuleManager.h"
#include "YetAnotherGraphEditor.h"

#define LOCTEXT_NAMESPACE "YetOtherAssetTypeActions"

FYetOtherAssetTypeActions::FYetOtherAssetTypeActions()
{
}

FText FYetOtherAssetTypeActions::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "GraphTypeActions", "Graph");
}

UClass * FYetOtherAssetTypeActions::GetSupportedClass() const
{
	return UYAGraph::StaticClass();
}

FColor FYetOtherAssetTypeActions::GetTypeColor() const
{
	return FColor::Red;
}

uint32 FYetOtherAssetTypeActions::GetCategories()
{
	return EAssetTypeCategories::Blueprint;
}

bool FYetOtherAssetTypeActions::HasActions(const TArray<UObject*>& InObjects) const
{
	return false;
}

void FYetOtherAssetTypeActions::OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor)
{
	FYetAnotherGraphEditorModule& Helper= FModuleManager::LoadModuleChecked<FYetAnotherGraphEditorModule>("YetAnotherGraphEditor");
	Helper.StartNodeHelper();

	EToolkitMode::Type Mode = EditWithinLevelEditor.IsValid() ? EToolkitMode::WorldCentric : EToolkitMode::Standalone;
	for (auto Object = InObjects.CreateConstIterator(); Object; Object++)
	{
		auto Graph = Cast<UYAGraph>(*Object);
		if (Graph != nullptr)
		{
			TSharedRef<FYetAnotherGraphEditorToolkit>EditorToolkit = MakeShareable(new FYetAnotherGraphEditorToolkit());
			EditorToolkit->InitGraphAssetEditor(Mode, EditWithinLevelEditor, Graph);
		}
	}
}

#undef LOCTEXT_NAMESPACE