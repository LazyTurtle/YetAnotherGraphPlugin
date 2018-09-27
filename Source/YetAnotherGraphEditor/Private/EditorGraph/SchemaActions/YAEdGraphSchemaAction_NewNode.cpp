#include "YAEdGraphSchemaAction_NewNode.h"
#include "YAGraph.h"
#include "YetAnotherEdGraphNode.h"
#include "EdGraph/EdGraph.h"

#define LOCTEXT_NAMESPACE "YAEdGraphSchemaAction_NewNode"

UEdGraphNode * FYAEdGraphSchemaAction_NewNode::PerformAction(UEdGraph * ParentGraph, UEdGraphPin * FromPin, const FVector2D Location, bool bSelectNewNode)
{
	check(ParentGraph);

	ParentGraph->Modify();


	UYAGraph* GraphAsset = CastChecked<UYAGraph>(ParentGraph->GetOuter());
	GraphAsset->Modify();

	UYANode* AssetNode = GraphAsset->SpawnNodeInsideGraph<UYANode>(NewNodeClass);


	FGraphNodeCreator<UYetAnotherEdGraphNode>Creator(*ParentGraph);
	UYetAnotherEdGraphNode* EdNode = Creator.CreateNode(bSelectNewNode);
	EdNode->SetAssetNode(AssetNode);

	EdNode->AllocateDefaultPins();
	EdNode->AutowireNewNode(FromPin);
	Creator.Finalize();

	EdNode->NodePosX = Location.X;
	EdNode->NodePosY = Location.Y;

	return CastChecked<UEdGraphNode>(EdNode);
}
#undef LOCTEXT_NAMESPACE