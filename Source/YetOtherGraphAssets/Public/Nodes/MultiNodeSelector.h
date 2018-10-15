// Copyright (c) 2018 Jhonny Hueller
#pragma once

#include "CoreMinimal.h"
#include "Nodes/FlowControlNode.h"
#include "YAGraph.h"
#include "MultiNodeSelector.generated.h"

#define LOCTEXT_NAMESPACE "MultiNodeSelector"

/**
 * 
 */
UCLASS(Abstract)
class YETOTHERGRAPHASSETS_API UMultiNodeSelector : public UFlowControlNode
{
	GENERATED_BODY()
	
public:

    UFUNCTION(BlueprintNativeEvent, Category = "Multi Node Selector")
    int32 IndexEvaluation(UObject* GraphOwner);
    virtual int32 IndexEvaluation_Implementation(UObject* GraphOwner) { return 0; }


    //inherited from YANode
    UYANode* GetNodePointer_Implementation() override;
	
	
};

#undef LOCTEXT_NAMESPACE