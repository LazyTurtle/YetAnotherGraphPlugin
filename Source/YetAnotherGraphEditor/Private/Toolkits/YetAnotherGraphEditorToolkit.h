// Copyright (c) 2018 Jhonny Hueller
#pragma once

#include "CoreMinimal.h"
#include "AssetEditorToolkit.h"
#include "NotifyHook.h"
#include "GraphEditor.h"
#include "IDetailsView.h"
#include "YAGraph.h"

/**
 * 
 */
class FYetAnotherGraphEditorToolkit : public FAssetEditorToolkit, public FNotifyHook
{
public:
	FYetAnotherGraphEditorToolkit();
	~FYetAnotherGraphEditorToolkit();

	// Inherited via FAssetEditorToolkit
	virtual FLinearColor GetWorldCentricTabColorScale() const override;
	virtual FName GetToolkitFName() const override;
	virtual FText GetBaseToolkitName() const override;
	virtual FString GetWorldCentricTabPrefix() const override;
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	virtual void SaveAsset_Execute() override;

	virtual void InitGraphAssetEditor(const EToolkitMode::Type InMode, const TSharedPtr<class IToolkitHost>& InToolkitHost, UYAGraph* InGraph);
	virtual void BlueprintCompiled();
private:

	static const FName DetailsTabId;
	static const FName GraphTabId;

	UYAGraph* GraphAsset;
	TSharedPtr<SGraphEditor> EdGraphEditor;
	TSharedPtr<IDetailsView> DetailsWidget;

	TSharedPtr<FUICommandList> GraphEditorCommands;

	FGraphPanelSelectionSet GetSelectedNodes();
	TSharedRef<SDockTab> HandleTabManagerSpawnTabDetails(const FSpawnTabArgs& Args);
	TSharedRef<SDockTab> HandleTabManagerSpawnTabGraph(const FSpawnTabArgs& Args);
	void BindToolkitCommands();

	//Delegates
	void OnCommandSelectAllNodes();
	bool CanSelectAllNodes();

	void OnCommandCopy();
	bool CanCopyNodes();

	void OnCommandPaste();
	bool CanPasteNodes();

	void OnCommandCut();
	bool CanCutNodes();

	void OnCommandDuplicate();
	bool CanDuplicateNodes();

	void OnCommandDelete();
	bool CanDeleteNodes();

};
