// Copyright (c) 2018 Jhonny Hueller
#include "FlowControlSchemaAction_NewNode.h"
#include "EdGraph/EdGraph.h"

UEdGraphNode * FFlowControlSchemaAction_NewNode::CreateEditorNode(UEdGraph * ParentGraph, bool bSelectNewNode, UYANode * AssetNode)
{
    FGraphNodeCreator<UFlowControlEdGraphNode>Creator(*ParentGraph);
    UFlowControlEdGraphNode* EdNode = Creator.CreateNode(bSelectNewNode);
    EdNode->SetAssetNode(AssetNode);
    Creator.Finalize();
    return EdNode;
}
