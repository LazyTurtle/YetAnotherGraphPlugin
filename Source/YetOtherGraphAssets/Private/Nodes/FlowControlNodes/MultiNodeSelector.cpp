// Copyright (c) 2018 Jhonny Hueller
#include "MultiNodeSelector.h"
#include "Logger.h"

#define LOCTEXT_NAMESPACE "MultiNodeSelector"

UYANode * UMultiNodeSelector::GetNodePointer_Implementation()
{
    int32 Index = IndexEvaluation(Graph->Owner);
    if ((ChildNodes.Num() == 0) || Index >= ChildNodes.Num())
    {
        ELog("There are %d nodes linked to a '%s' node and the index evaluated is &d.", ChildNodes.Num(), *StaticClass()->GetDisplayNameText().ToString(), Index);
        return nullptr;
    }
    return (ChildNodes.IsValidIndex(Index)) ? ChildNodes[Index]->GetNodePointer() : nullptr;
}

#undef LOCTEXT_NAMESPACE