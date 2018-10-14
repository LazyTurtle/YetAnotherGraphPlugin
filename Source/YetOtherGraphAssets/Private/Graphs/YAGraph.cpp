// Copyright (c) 2018 Jhonny Hueller
#include "YAGraph.h"
#include "YANode.h"
#include "StartNode.h"
#define LOCTEXT_NAMESPACE "UYAGraph"

UYAGraph::UYAGraph()
{
    
#if WITH_EDITORONLY_DATA
	EdGraph = nullptr;
#endif

}

TArray<UStartNode*> UYAGraph::GetStartingNodes()
{
	TArray<UStartNode*>NodesArray;
	for (UYANode* Node:Nodes)
	{
		if (UStartNode* StartNode = Cast<UStartNode>(Node))
			NodesArray.Add(StartNode);
	}
	return NodesArray;
}

#if WITH_EDITORONLY_DATA
void UYAGraph::AddNode(UYANode * InNode)
{
	InNode->SetGraph(this);
	InNode->Rename(nullptr, this);
	int32 Index = Nodes.Add(InNode);
	LLog("Spawned node at index %d", Index);
}

void UYAGraph::RemoveNode(UYANode * NodeToRemove)
{
	for (UYANode* Node : Nodes)
	{
		Node->RemoveLinkedNode(NodeToRemove);
	}

	int32 Removed=Nodes.Remove(NodeToRemove);

	if (Removed > 0)
	{
		LLog("Node Removed.");
	}
	else
	{
		ELog("The node is not present inside the graph.");
	}
}
#endif

#undef LOCTEXT_NAMESPACE