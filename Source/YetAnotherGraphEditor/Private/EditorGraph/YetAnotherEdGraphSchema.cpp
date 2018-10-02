#include "YetAnotherEdGraphSchema.h"
#include "SubclassOf.h"
#include "EditorLogger.h"
#include "YAConnectionDrawingPolicy.h"
#include "UObjectIterator.h"
#include "YAEdGraphSchemaAction_NewNode.h"
#include "EdGraph/EdGraph.h"
#include "StartNode.h"
#include "YAGraph.h"
#include "YetAnotherEdGraphNode.h"
#include "YetAnotherNodeClassHelper.h"
#include "ModuleManager.h"
#include "YetAnotherGraphEditor.h"

#define LOCTEXT_NAMESPACE "YetAnotherEdGraphSchema"

UYetAnotherEdGraphSchema::UYetAnotherEdGraphSchema(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer){}

void UYetAnotherEdGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder & ContextMenuBuilder) const
{

	FText ToolTip = LOCTEXT("NewYetAnotherNodeTooltip", "Add a {NodeName} to the graph.");
	FText MenuDesc = LOCTEXT("NewYetAnotherNodeDescription", "{NodeName}");
	
	EDLLog("Gathering C++ classes.");

	FCategorizedGraphActionListBuilder BaseBuilder(TEXT("Base Nodes"));
	TArray<TSubclassOf<UYANode>> BasicNodes;

	for (TObjectIterator<UClass> It; It; ++It)
	{
		if (It->IsChildOf(UYANode::StaticClass()) && !It->HasAnyClassFlags(CLASS_Abstract) && It->HasAnyClassFlags(CLASS_Native))
		{
			FFormatNamedArguments Arguments;
			Arguments.Add(TEXT("NodeName"), It->GetDisplayNameText());
			TSharedPtr<FYAEdGraphSchemaAction_NewNode> NewNodeAction(new FYAEdGraphSchemaAction_NewNode(FText(), FText::Format(MenuDesc, Arguments), FText::Format(ToolTip, Arguments), 0, *It));
			BaseBuilder.AddAction(NewNodeAction);
			EDLLog("%s added", *It->GetDisplayNameText().ToString());
		}
	}

	ContextMenuBuilder.Append(BaseBuilder);
	
	EDLLog("Gathering child blueprints.");

	FYetAnotherGraphEditorModule& YAModule = FModuleManager::GetModuleChecked<FYetAnotherGraphEditorModule>("YetAnotherGraphEditor");
	TSharedPtr<FYetAnotherNodeClassHelper> Helper = YAModule.GetHelper();

	TArray<FYetAnotherNodeClassData> BlueprintClasses;
	Helper->GatherClasses(USimpleNode::StaticClass(), BlueprintClasses);

	FCategorizedGraphActionListBuilder BlueprintBuilder(TEXT("User Defined Nodes"));

	for (auto& BlueprintClassData : BlueprintClasses)
	{
		if (!BlueprintClassData.GetClass()->HasAnyClassFlags(CLASS_Native))
		{
			FFormatNamedArguments Arguments;
			Arguments.Add(TEXT("NodeName"), BlueprintClassData.GetClass()->GetDisplayNameText());
			TSharedPtr<FYAEdGraphSchemaAction_NewNode> NewNodeAction(new FYAEdGraphSchemaAction_NewNode(FText(), FText::Format(MenuDesc, Arguments), FText::Format(ToolTip, Arguments), 0, BlueprintClassData.GetClass()));
			BlueprintBuilder.AddAction(NewNodeAction);
			EDLLog("%s", *BlueprintClassData.GetClass()->GetName());
		}
	}

	ContextMenuBuilder.Append(BlueprintBuilder);
}

void UYetAnotherEdGraphSchema::GetContextMenuActions(const UEdGraph * CurrentGraph, const UEdGraphNode * InGraphNode, const UEdGraphPin * InGraphPin, FMenuBuilder * MenuBuilder, bool bIsDebugging) const
{
}

const FPinConnectionResponse UYetAnotherEdGraphSchema::CanCreateConnection(const UEdGraphPin * A, const UEdGraphPin * B) const
{
	if(!(A && B))
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Both pins must be available."));

	if (A->GetOwningNode() == B->GetOwningNode())
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("You can't connect a node to itself."));

	if (A->Direction == EGPD_Input && B->Direction == EGPD_Input)
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("You can't connect an input pin to another input pin."));

	if (A->Direction == EGPD_Output && B->Direction == EGPD_Output)
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("You can't connect an output pin to another output pin"));

	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, TEXT(""));
}

FConnectionDrawingPolicy * UYetAnotherEdGraphSchema::CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect & InClippingRect, FSlateWindowElementList & InDrawElements, UEdGraph * InGraphObj) const
{
	return new FYAConnectionDrawingPolicy(InBackLayerID, InFrontLayerID, InZoomFactor, InClippingRect, InDrawElements, InGraphObj);
}

void UYetAnotherEdGraphSchema::CreateDefaultNodesForGraph(UEdGraph & Graph) const
{
	if (Graph.Nodes.Num() == 0)
	{
		UYAGraph* GraphAsset = Cast<UYAGraph>(Graph.GetOuter());

		GraphAsset->Modify();
		Graph.Modify();
		
		UYANode* AssetNode = GraphAsset->SpawnNodeInsideGraph<UYANode>(UStartNode::StaticClass());


		FGraphNodeCreator<UYetAnotherEdGraphNode>Creator(Graph);
		UYetAnotherEdGraphNode* EdNode = Creator.CreateNode();
		EdNode->SetAssetNode(AssetNode);
		EdNode->AllocateDefaultPins();

		Creator.Finalize();

		EdNode->NodePosX = 0;
		EdNode->NodePosY = 0;
	}
}
#undef LOCTEXT_NAMESPACE