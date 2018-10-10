

#include "FlowControlEdGraphNode.h"

void UFlowControlEdGraphNode::SaveNodesAsChildren(TArray<UEdGraphNode*>& Children)
{
    while (Children.Num()>0)
    {
        UEdGraphNode* Node = GetMostLeftNode(Children);
        if(UYetAnotherEdGraphNode* YaNode = Cast<UYetAnotherEdGraphNode>(Node))
            AssetNode->LinkArgumentNodeAsChild(YaNode->AssetNode);
        Children.Remove(Node);
    }
}

UEdGraphNode * UFlowControlEdGraphNode::GetMostLeftNode(TArray<UEdGraphNode*>& Nodes)
{
    auto* Node = Nodes[0] ? Nodes[0] : nullptr;
    for (auto* N : Nodes)
    {
        if (N->NodePosX < Node->NodePosX)
            Node = N;
    }
    return Node;
}
