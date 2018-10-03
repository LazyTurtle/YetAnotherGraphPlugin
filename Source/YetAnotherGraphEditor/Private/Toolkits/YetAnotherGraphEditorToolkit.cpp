#include "YetAnotherGraphEditorToolkit.h"
#include "EditorLogger.h"
#include "PropertyEditorModule.h"
#include "ModuleManager.h"
#include "Slate.h"
#include "BlueprintEditorUtils.h"
#include "GraphEditorActions.h"
#include "YAEdGraph.h"
#include "YetAnotherEdGraphSchema.h"
#include "EdGraphUtilities.h"
#include "PlatformApplicationMisc.h"
#include "YetAnotherEdGraphNode.h"
#include "Editor.h"


#define LOCTEXT_NAMESPACE "YetAnotherGraphEditorToolkit"

const FName FYetAnotherGraphEditorToolkit::DetailsTabId(TEXT("YetAnotherGraphEditorToolkitDetailsTabId"));
const FName FYetAnotherGraphEditorToolkit::GraphTabId(TEXT("YetAnotherGraphEditorToolkitGraphTabId"));


FYetAnotherGraphEditorToolkit::FYetAnotherGraphEditorToolkit()
{
	GEditor->OnBlueprintCompiled().AddRaw(this,&FYetAnotherGraphEditorToolkit::BlueprintCompiled);
}

FYetAnotherGraphEditorToolkit::~FYetAnotherGraphEditorToolkit()
{
	GEditor->OnBlueprintCompiled().RemoveAll(this);
}



FGraphPanelSelectionSet FYetAnotherGraphEditorToolkit::GetSelectedNodes()
{
	return EdGraphEditor->GetSelectedNodes();
}

TSharedRef<SDockTab> FYetAnotherGraphEditorToolkit::HandleTabManagerSpawnTabDetails(const FSpawnTabArgs & Args)
{

	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.bUpdatesFromSelection = false;
	DetailsViewArgs.bCustomNameAreaLocation = false;
	DetailsViewArgs.bLockable = false;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
	DetailsViewArgs.NotifyHook = this;

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");

	DetailsWidget = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	DetailsWidget->SetObject(GraphAsset);

	return SNew(SDockTab)
		.TabRole(ETabRole::PanelTab)
		[
			DetailsWidget.ToSharedRef()
		];
}

TSharedRef<SDockTab> FYetAnotherGraphEditorToolkit::HandleTabManagerSpawnTabGraph(const FSpawnTabArgs & Args)
{

	if (GraphAsset->EdGraph != nullptr)
	{
		EdGraphEditor = SNew(SGraphEditor)
			.AdditionalCommands(GraphEditorCommands)
			.GraphToEdit(GraphAsset->EdGraph);
	}
	else
	{
		EDELog("There is no editor graph inside the graph asset.");
	}
	return SNew(SDockTab)
		.TabRole(ETabRole::PanelTab)
		[
			EdGraphEditor.ToSharedRef()
		];
}

FLinearColor FYetAnotherGraphEditorToolkit::GetWorldCentricTabColorScale() const
{
	return FLinearColor::Blue;
}

FName FYetAnotherGraphEditorToolkit::GetToolkitFName() const
{
	return FName("Graph Editor");
}

FText FYetAnotherGraphEditorToolkit::GetBaseToolkitName() const
{
	return LOCTEXT("AppLabel", "Graph Editor");
}

FString FYetAnotherGraphEditorToolkit::GetWorldCentricTabPrefix() const
{
	return LOCTEXT("WorldCentricTabPrefix", "Graph").ToString();
}

void FYetAnotherGraphEditorToolkit::InitGraphAssetEditor(const EToolkitMode::Type InMode, const TSharedPtr<class IToolkitHost>& InToolkitHost, UYAGraph * InGraph)
{
	GraphAsset = InGraph;
	if (GraphAsset->EdGraph == nullptr)
	{
		EDLLog("Creating a new graph.");
		GraphAsset->EdGraph = CastChecked<UYAEdGraph>(FBlueprintEditorUtils::CreateNewGraph(GraphAsset, NAME_None, UYAEdGraph::StaticClass(), UYetAnotherEdGraphSchema::StaticClass()));
		GraphAsset->EdGraph->bAllowDeletion = false;

		//Give the schema a chance to fill out any required nodes (like the results node)
		const UEdGraphSchema* Schema = GraphAsset->EdGraph->GetSchema();
		Schema->CreateDefaultNodesForGraph(*GraphAsset->EdGraph);
	}

	FGenericCommands::Register();
	FGraphEditorCommands::Register();
	BindToolkitCommands();

	TSharedRef<FTabManager::FLayout>Layout = FTabManager::NewLayout("Layout_1")
		->AddArea
		(
			FTabManager::NewPrimaryArea()
			->SetOrientation(Orient_Vertical)
			->Split
			(
				FTabManager::NewStack()
				->AddTab(GetToolbarTabId(), ETabState::OpenedTab)
				->SetHideTabWell(true)
				->SetSizeCoefficient(0.2f)
			)
			->Split
			(
				FTabManager::NewSplitter()
				->SetOrientation(Orient_Horizontal)
				->SetSizeCoefficient(0.8f)
				->Split
				(
					FTabManager::NewStack()
					->AddTab(DetailsTabId, ETabState::OpenedTab)
					->SetHideTabWell(true)
					->SetSizeCoefficient(0.15f)
				)
				->Split
				(
					FTabManager::NewStack()
					->AddTab(GraphTabId, ETabState::OpenedTab)
					->SetHideTabWell(true)
					->SetSizeCoefficient(0.85f)
				)
			)
		);

	FAssetEditorToolkit::InitAssetEditor(InMode, InToolkitHost, FName("GraphEditorIdentifier"), Layout, true, true, GraphAsset);
}

void FYetAnotherGraphEditorToolkit::BlueprintCompiled()
{
	UEdGraph* EdGraph = EdGraphEditor->GetCurrentGraph();
	if (UYAEdGraph* MyGraph = Cast<UYAEdGraph>(EdGraph))
		MyGraph->RefreshNodes();
}

void FYetAnotherGraphEditorToolkit::SaveAsset_Execute()
{
	if (GraphAsset && GraphAsset->EdGraph)
	{
		UYAEdGraph* EdGraph = Cast<UYAEdGraph>(GraphAsset->EdGraph);
		EdGraph->LinkAssetNodes();
	}
	FAssetEditorToolkit::SaveAsset_Execute();
}

void FYetAnotherGraphEditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager)
{

	WorkspaceMenuCategory = TabManager->AddLocalWorkspaceMenuCategory(LOCTEXT("YetAnotherToolkitWorkspaceMenu", "Graph Editor"));
	auto WorkspaceMenuCategoryRef = WorkspaceMenuCategory.ToSharedRef();
	
	TabManager->RegisterTabSpawner(DetailsTabId, FOnSpawnTab::CreateSP(this, &FYetAnotherGraphEditorToolkit::HandleTabManagerSpawnTabDetails))
		.SetDisplayName(LOCTEXT("DetailsTab", "Details"))
		.SetGroup(WorkspaceMenuCategoryRef);
	TabManager->RegisterTabSpawner(GraphTabId, FOnSpawnTab::CreateSP(this, &FYetAnotherGraphEditorToolkit::HandleTabManagerSpawnTabGraph))
		.SetDisplayName(LOCTEXT("GraphTab", "Graph Editor"))
		.SetGroup(WorkspaceMenuCategoryRef);

	FAssetEditorToolkit::RegisterTabSpawners(TabManager);
}

void FYetAnotherGraphEditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(TabManager);
	TabManager->UnregisterTabSpawner(DetailsTabId);
	TabManager->UnregisterTabSpawner(GraphTabId);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Commands and Bindings
void FYetAnotherGraphEditorToolkit::BindToolkitCommands()
{
	if (!GraphEditorCommands.IsValid())
	{
		GraphEditorCommands = MakeShareable(new FUICommandList());

		GraphEditorCommands->MapAction
		(
			FGenericCommands::Get().SelectAll,
			FExecuteAction::CreateRaw(this, &FYetAnotherGraphEditorToolkit::OnCommandSelectAllNodes),
			FCanExecuteAction::CreateRaw(this, &FYetAnotherGraphEditorToolkit::CanSelectAllNodes)
		);

		GraphEditorCommands->MapAction
		(
			FGenericCommands::Get().Cut,
			FExecuteAction::CreateRaw(this, &FYetAnotherGraphEditorToolkit::OnCommandCut),
			FCanExecuteAction::CreateRaw(this, &FYetAnotherGraphEditorToolkit::CanCutNodes)
		);

		GraphEditorCommands->MapAction
		(
			FGenericCommands::Get().Copy,
			FExecuteAction::CreateRaw(this, &FYetAnotherGraphEditorToolkit::OnCommandCopy),
			FCanExecuteAction::CreateRaw(this, &FYetAnotherGraphEditorToolkit::CanCopyNodes)
		);

		GraphEditorCommands->MapAction
		(
			FGenericCommands::Get().Paste,
			FExecuteAction::CreateRaw(this, &FYetAnotherGraphEditorToolkit::OnCommandPaste),
			FCanExecuteAction::CreateRaw(this, &FYetAnotherGraphEditorToolkit::CanPasteNodes)
		);

		GraphEditorCommands->MapAction
		(
			FGenericCommands::Get().Duplicate,
			FExecuteAction::CreateRaw(this, &FYetAnotherGraphEditorToolkit::OnCommandDuplicate),
			FCanExecuteAction::CreateRaw(this, &FYetAnotherGraphEditorToolkit::CanDuplicateNodes)
		);

		GraphEditorCommands->MapAction
		(
			FGenericCommands::Get().Delete,
			FExecuteAction::CreateRaw(this, &FYetAnotherGraphEditorToolkit::OnCommandDelete),
			FCanExecuteAction::CreateRaw(this, &FYetAnotherGraphEditorToolkit::CanDeleteNodes)
		);

	}
}

void FYetAnotherGraphEditorToolkit::OnCommandSelectAllNodes()
{
	if (EdGraphEditor.IsValid())
		EdGraphEditor->SelectAllNodes();
}

bool FYetAnotherGraphEditorToolkit::CanSelectAllNodes()
{
	return true;
}

void FYetAnotherGraphEditorToolkit::OnCommandCut()
{
	OnCommandCopy();

	const FGraphPanelSelectionSet OldSelectedNodes = EdGraphEditor->GetSelectedNodes();
	EdGraphEditor->ClearSelectionSet();
	for (FGraphPanelSelectionSet::TConstIterator It(OldSelectedNodes); It; ++It)
	{
		UEdGraphNode* Node = Cast<UEdGraphNode>(*It);
		if (Node && Node->CanDuplicateNode())
		{
			EdGraphEditor->SetNodeSelection(Node, true);
		}
	}

	OnCommandDelete();

	EdGraphEditor->ClearSelectionSet();

	for (FGraphPanelSelectionSet::TConstIterator It(OldSelectedNodes); It; ++It)
	{
		UEdGraphNode* Node = Cast<UEdGraphNode>(*It);
		if (Node)
			EdGraphEditor->SetNodeSelection(Node, true);
	}
}

bool FYetAnotherGraphEditorToolkit::CanCutNodes()
{
	return true;
}

void FYetAnotherGraphEditorToolkit::OnCommandCopy()
{
	FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();
	FString ExportedText;

	for (FGraphPanelSelectionSet::TIterator it(SelectedNodes); it; ++it)
	{
		UEdGraphNode* Node = Cast<UEdGraphNode>(*it);
		if (Node)
			Node->PrepareForCopying();
		else
			it.RemoveCurrent();
	}

	FEdGraphUtilities::ExportNodesToText(SelectedNodes, ExportedText);
	FPlatformApplicationMisc::ClipboardCopy(*ExportedText);

	for (FGraphPanelSelectionSet::TIterator it(SelectedNodes); it; ++it)
	{
		UYetAnotherEdGraphNode* Node = Cast<UYetAnotherEdGraphNode>(*it);
		if (Node)
			Node->PostCopyNode();
	}
}

bool FYetAnotherGraphEditorToolkit::CanCopyNodes()
{
	return true;
}

void FYetAnotherGraphEditorToolkit::OnCommandPaste()
{

	const FVector2D PasteLocation = EdGraphEditor->GetPasteLocation();

	UEdGraph* EdGraph = EdGraphEditor->GetCurrentGraph();
	EdGraph->Modify();
	EdGraphEditor->ClearSelectionSet();

	FString ExportedText;
	FPlatformApplicationMisc::ClipboardPaste(ExportedText);
	TSet<UEdGraphNode*> ImportedNodes;
	FEdGraphUtilities::ImportNodesFromText(EdGraph, ExportedText, ImportedNodes);

	for (TSet<UEdGraphNode*>::TIterator It(ImportedNodes); It; ++It)
	{
		UYetAnotherEdGraphNode* Node = Cast<UYetAnotherEdGraphNode>(*It);
		GraphAsset->AddNode(Node->AssetNode);
	}

	FVector2D AvgNodePosition(0.0f, 0.0f);

	for (TSet<UEdGraphNode*>::TIterator It(ImportedNodes); It; ++It)
	{
		UEdGraphNode* Node = *It;
		AvgNodePosition.X += Node->NodePosX;
		AvgNodePosition.Y += Node->NodePosY;
	}

	float InvNumNodes = 1.0f / float(ImportedNodes.Num());
	AvgNodePosition.X *= InvNumNodes;
	AvgNodePosition.Y *= InvNumNodes;

	for (TSet<UEdGraphNode*>::TIterator It(ImportedNodes); It; ++It)
	{
		UEdGraphNode* Node = *It;
		EdGraphEditor->SetNodeSelection(Node, true);

		Node->NodePosX = (Node->NodePosX - AvgNodePosition.X) + PasteLocation.X;
		Node->NodePosY = (Node->NodePosY - AvgNodePosition.Y) + PasteLocation.Y;

		Node->SnapToGrid(16);

		// Give new node a different Guid from the old one
		Node->CreateNewGuid();
	}

	EdGraphEditor->NotifyGraphChanged();

	UObject* GraphOwner = EdGraph->GetOuter();
	if (GraphOwner)
	{
		GraphOwner->PostEditChange();
		GraphOwner->MarkPackageDirty();
	}

}

bool FYetAnotherGraphEditorToolkit::CanPasteNodes()
{
	return true;
}

void FYetAnotherGraphEditorToolkit::OnCommandDuplicate()
{
	OnCommandCopy();
	OnCommandPaste();
}

bool FYetAnotherGraphEditorToolkit::CanDuplicateNodes()
{
	return true;
}

void FYetAnotherGraphEditorToolkit::OnCommandDelete()
{

	EdGraphEditor->GetCurrentGraph()->Modify();

	const FGraphPanelSelectionSet SelectedNodes = GetSelectedNodes();
	EdGraphEditor->ClearSelectionSet();

	for (FGraphPanelSelectionSet::TConstIterator It(SelectedNodes); It; ++It)
	{
		if (UEdGraphNode* Node = Cast<UEdGraphNode>(*It))
		{
			Node->Modify();
			Node->DestroyNode();
		}
	}
}

bool FYetAnotherGraphEditorToolkit::CanDeleteNodes()
{
	return true;
}

// END Commands and binding
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE