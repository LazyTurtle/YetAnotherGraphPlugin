#include "YANode.h"
#include "YAGraph.h"

#define LOCTEXT_NAMESPACE "YANode" 

UYANode::UYANode()
{
	DefaultNodeTitle = LOCTEXT("Node Title", "Node");
}

void UYANode::SetGraph(UYAGraph * InGraph)
{
	Graph = InGraph;
}

UYAGraph * UYANode::GetGraph()
{
	return Graph;
}

FText UYANode::GetNodeTitle()
{
	FText Title = InternalGetNodeTitle();

	return Title.IsEmpty() ? LOCTEXT("Node Title", "Node") : Title;
}

TArray<UYANode*> UYANode::GetChildren()
{
	return ChildNodes;
}

TArray<UYANode*> UYANode::GetParents()
{
	return ParentNodes;
}

FText UYANode::InternalGetNodeTitle_Implementation()
{
	return DefaultNodeTitle;
}

bool UYANode::HasInputPins_Implementation()
{
	return bHasInputPins;
}

bool UYANode::HasOutputPins_Implementation()
{
	return bHasOutputPins;
}

void UYANode::AddToChildren(UYANode * NewSubNode)
{
	ChildNodes.Add(NewSubNode);
}

void UYANode::AddToParent(UYANode * NewParentNode)
{
	ParentNodes.Add(NewParentNode);
}

bool UYANode::HasParentNodes()
{
	return ParentNodes.Num() > 0;
}

void UYANode::LinkArgumentNodeAsChild(UYANode * Child)
{
	AddToChildren(Child);
	Child->AddToParent(this);
}

void UYANode::ClearLinks()
{
	ParentNodes.Empty();
	ChildNodes.Empty();
}

bool UYANode::RemoveLinkedNode(UYANode * NodeToRemove)
{
	return RemoveNodeFromParents(NodeToRemove) || RemoveNodeFromChilds(NodeToRemove);
}

bool UYANode::RemoveNodeFromParents(UYANode * NodeToRemove)
{
	return ParentNodes.Remove(NodeToRemove);
}

bool UYANode::RemoveNodeFromChilds(UYANode * NodeToRemove)
{
	return ChildNodes.Remove(NodeToRemove);
}

#undef LOCTEXT_NAMESPACE