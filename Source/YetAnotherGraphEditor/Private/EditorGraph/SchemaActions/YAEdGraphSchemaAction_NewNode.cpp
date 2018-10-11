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

    UEdGraphNode* EditorNode=CreateEditorNode(ParentGraph,bSelectNewNode,AssetNode);
	
    //EditorNode->AllocateDefaultPins();   for some reason it was called 2 times even if I only call it here
    EditorNode->AutowireNewNode(FromPin);
    EditorNode->NodePosX = Location.X;
    EditorNode->NodePosY = Location.Y;

	return EditorNode;
}
UEdGraphNode * FYAEdGraphSchemaAction_NewNode::CreateEditorNode(UEdGraph * ParentGraph, bool bSelectNewNode, UYANode* AssetNode)
{
    FGraphNodeCreator<UYetAnotherEdGraphNode>Creator(*ParentGraph);
    UYetAnotherEdGraphNode* EdNode = Creator.CreateNode(bSelectNewNode);
    EdNode->SetAssetNode(AssetNode);
    Creator.Finalize();
    return EdNode;
}
#undef LOCTEXT_NAMESPACE