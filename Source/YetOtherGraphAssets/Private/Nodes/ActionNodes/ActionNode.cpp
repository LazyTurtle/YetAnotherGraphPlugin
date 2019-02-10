// Copyright (c) 2018 Jhonny Hueller

#include "ActionNode.h"
#include "Logger.h"
#include "Array.h"

#define LOCTEXT_NAMESPACE "ActionNode"

UActionNode::UActionNode()
{
    DefaultNodeTitle= LOCTEXT("ActionNode", "Action Node");
}

UYANode * UActionNode::GetNodePointer_Implementation()
{
    if (ChildNodes.Num() <= 1)
    {
        ActionToPerform(Graph->Owner);
        return (ChildNodes.IsValidIndex(0)) ? ChildNodes[0]->GetNodePointer() : nullptr;
    }
    else
    {
        ELog("There should be at most one subnode on an ActionNode");
        return nullptr;
    }
}

#undef LOCTEXT_NAMESPACE
