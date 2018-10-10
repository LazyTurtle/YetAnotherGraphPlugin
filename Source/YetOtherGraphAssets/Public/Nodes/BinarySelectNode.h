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
        bool BooleanEvaluation();
    virtual bool BooleanEvaluation_Implementation() { return false; }
	

    //inherited from YANode
    UYANode* GetNodePointer_Implementation() override;

protected:
    UPROPERTY()
        int32 MaxNumberOfSubNodes = 2;
	
};
