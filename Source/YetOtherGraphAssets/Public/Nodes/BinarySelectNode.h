// Copyright (c) 2018 Jhonny Hueller
#pragma once

#include "CoreMinimal.h"
#include "FlowControlNode.h"
#include "BinarySelectNode.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class YETOTHERGRAPHASSETS_API UBinarySelectNode : public UFlowControlNode
{
	GENERATED_BODY()
	
public:
    UBinarySelectNode();

    UFUNCTION(BlueprintNativeEvent, Category = "Binary Selector")
        bool BooleanEvaluation(UObject* GraphOwner);
    virtual bool BooleanEvaluation_Implementation(UObject* GraphOwner) { return false; }
	

    //inherited from YANode
    UYANode* GetNodePointer_Implementation() override;

protected:
    UPROPERTY()
        int32 MaxNumberOfSubNodes = 2;
	
};
