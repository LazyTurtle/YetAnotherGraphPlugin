// Copyright (c) 2018 Jhonny Hueller
#pragma once

#include "CoreMinimal.h"
#include "YetAnotherEdGraphNode.h"
#include "FlowControlEdGraphNode.generated.h"

/**
 * 
 */
UCLASS()
class UFlowControlEdGraphNode : public UYetAnotherEdGraphNode
{
	GENERATED_BODY()
	
	//Inherited from UYetAnotherEdGraphNode
    void SaveNodesAsChildren(TArray<UEdGraphNode*>& Children) override; //we are going to save the nodes in order from left to right
	
    virtual UEdGraphNode* GetMostLeftNode(TArray<UEdGraphNode*>& Nodes);
};
