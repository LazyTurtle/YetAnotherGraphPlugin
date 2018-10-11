#pragma once

#include "CoreMinimal.h"
#include "YAEdGraphSchemaAction_NewNode.h"
#include "FlowControlEdGraphNode.h"
#include "FlowControlSchemaAction_NewNode.generated.h"

/**
 * 
 */
USTRUCT()
struct FFlowControlSchemaAction_NewNode : public FYAEdGraphSchemaAction_NewNode
{
public:

    GENERATED_USTRUCT_BODY()

    FFlowControlSchemaAction_NewNode() :FYAEdGraphSchemaAction_NewNode() {}
    FFlowControlSchemaAction_NewNode(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping, TSubclassOf<UYANode> InNodeClass) :FYAEdGraphSchemaAction_NewNode(InNodeCategory, InMenuDesc, InToolTip, InGrouping, InNodeClass) {}


    //Inherited from FYAEdGraphSchemaAction_NewNode
    UEdGraphNode* CreateEditorNode(UEdGraph * ParentGraph, bool bSelectNewNode, UYANode* AssetNode) override;
};
