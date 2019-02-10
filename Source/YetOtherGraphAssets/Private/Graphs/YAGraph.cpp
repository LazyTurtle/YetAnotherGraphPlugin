// Copyright (c) 2018 Jhonny Hueller
#include "YAGraph.h"
#include "YANode.h"
#include "StartNode.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"

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

void UYAGraph::InitGraph(UObject * ParentObject)
{
    Owner = ParentObject;
    Rename(nullptr, ParentObject);
}


#if WITH_ENGINE

UWorld * UYAGraph::GetWorld() const
{
    if (GetOuter()->IsA(UActorComponent::StaticClass()) || GetOuter()->IsA(AActor::StaticClass()))
    {
        return GetOuter()->GetWorld();
    }
    else
    {
        return nullptr;
    }
}

#endif

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