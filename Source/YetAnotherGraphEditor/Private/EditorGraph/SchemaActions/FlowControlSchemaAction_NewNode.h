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


    //Inherited from FYAEdGraphSchemaAction_NewNode
    UEdGraphNode* CreateEditorNode(UEdGraph * ParentGraph, bool bSelectNewNode, UYANode* AssetNode) override;
};
