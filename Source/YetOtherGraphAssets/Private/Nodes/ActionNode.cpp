// Copyright (c) 2018 Jhonny Hueller

#include "ActionNode.h"
#include "Logger.h"

#define LOCTEXT_NAMESPACE "ActionNode"

UActionNode::UActionNode()
{
    DefaultNodeTitle= LOCTEXT("ActionNode", "Action Node");
}

UYANode * UActionNode::GetNodePointer_Implementation()
{
    if (ChildNodes.Num() != 1)
    {
        ELog("There should be only one subnode on an ActionNode");
        return nullptr;
    }
    else
    {
        ActionToPerform(Graph->Owner);
        return ChildNodes[0];
    }
}

#undef LOCTEXT_NAMESPACE
