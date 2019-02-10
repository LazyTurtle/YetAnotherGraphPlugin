// Copyright (c) 2018 Jhonny Hueller

#include "NthSelector.h"
#include "YAGraph.h"
#include "Logger.h"
#include "YetAnotherGraphInterface.h"
#include "GraphSupportComponent.h"
#include "GraphSupportComponentInterface.h"

#define LOCTEXT_NAMESPACE "NthSelector"

UNthSelector::UNthSelector()
{
    DefaultNodeTitle= LOCTEXT("NthSelector", "'Nth Selector");
}

int32 UNthSelector::IndexEvaluation_Implementation(UObject* GraphOwner)
{
    int32 Integer = 0;
    bool Result = false;
    UObject* Support=nullptr;

    if (GraphOwner->GetClass()->ImplementsInterface(UGraphSupportComponentInterface::StaticClass()))
    {
        IGraphSupportComponentInterface* Interface = Cast<IGraphSupportComponentInterface>(GraphOwner);
        Support = Interface->Execute_GetGraphSupportComponent(GraphOwner);
    }
    else
        if (GraphOwner->GetClass()->ImplementsInterface(UYetAnotherGraphInterface::StaticClass()))
            Support = GraphOwner;

    if (Support != nullptr)
    {
        IYetAnotherGraphInterface* Interface = Cast<IYetAnotherGraphInterface>(Support);
        if (Interface)
            Integer = Interface->Execute_GetIntegerVariable(Support, IndexName, Result);
    }
    else
        ELog("No graph interfaces has been found.");

    if (!Result)
        ELog("%s:Error upon looking for an integer", *GraphOwner->GetClass()->GetDisplayNameText().ToString());

   
    return Integer;
}

#undef LOCTEXT_NAMESPACE
