// Copyright (c) 2018 Jhonny Hueller
#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "SubclassOf.h"
#include "YANode.h"
#include "YAEdGraphSchemaAction_NewNode.generated.h"

/**
 * 
 */
USTRUCT()
struct FYAEdGraphSchemaAction_NewNode : public FEdGraphSchemaAction
{
public:
	GENERATED_USTRUCT_BODY()

	FYAEdGraphSchemaAction_NewNode() :FEdGraphSchemaAction(), NewNodeClass(nullptr) {}
	FYAEdGraphSchemaAction_NewNode(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping, TSubclassOf<UYANode> InNodeClass) :FEdGraphSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InGrouping), NewNodeClass(InNodeClass) {}

	/** Execute this action, given the graph and schema, and possibly a pin that we were dragged from. Returns a node that was created by this action (if any). */
	UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;

    virtual UEdGraphNode* CreateEditorNode(UEdGraph * ParentGraph, bool bSelectNewNode, UYANode* AssetNode);
	TSubclassOf<UYANode>NewNodeClass;


};
