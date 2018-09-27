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

#define LOCTEXT_NAMESPACE "YetAnotherEdGraphSchema"

TSet<TSubclassOf<UYANode>> UYetAnotherEdGraphSchema::NodeClasses;

UYetAnotherEdGraphSchema::UYetAnotherEdGraphSchema(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer){}

void UYetAnotherEdGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder & ContextMenuBuilder) const
{

	FText ToolTip = LOCTEXT("NewYetAnotherNodeTooltip", "Add a {NodeName} to the graph.");
	FText MenuDesc = LOCTEXT("NewYetAnotherNodeDescription", "{NodeName}");

	InitNodeClasses();

	FFormatNamedArguments Arguments;

	for (TSubclassOf<UYANode> NodeClass : NodeClasses)
	{
		Arguments.Add(TEXT("NodeName"), NodeClass->GetDisplayNameText());
		TSharedPtr<FYAEdGraphSchemaAction_NewNode> NewNodeAction(new FYAEdGraphSchemaAction_NewNode(LOCTEXT("YetAnotherGraphEdGraphSchema", "YetAnother Graph"), FText::Format(MenuDesc, Arguments), FText::Format(ToolTip, Arguments), 0, NodeClass));
		ContextMenuBuilder.AddAction(NewNodeAction);
	}

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

void UYetAnotherEdGraphSchema::InitNodeClasses()
{
	NodeClasses.Empty();
	for (TObjectIterator<UClass> It; It; ++It)
	{
		if (It->IsChildOf(UYANode::StaticClass()) && !It->HasAnyClassFlags(CLASS_Abstract))
		{
			EDLLog("%s", *It->GetDefaultObjectName().ToString())

			/////////////////////////////////////////////////////////////find a way to remove SKEL and REINST nodes from the list that doesn't use the name as a filter
			
			NodeClasses.Add(*It);
		}
	}
}
#undef LOCTEXT_NAMESPACE