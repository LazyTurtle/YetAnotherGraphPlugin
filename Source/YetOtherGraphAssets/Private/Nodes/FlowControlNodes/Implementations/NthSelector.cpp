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

    if (GraphOwner->StaticClass()->ImplementsInterface(UGraphSupportComponent::StaticClass()))
    {
        IGraphSupportComponentInterface* Interface = Cast<IGraphSupportComponentInterface>(GraphOwner);
        Support = Interface->GetGraphSupportComponent();
    }
    else
    {
        WLog("The object %s does not implement the graph support interface.", *GraphOwner->StaticClass()->GetDisplayNameText().ToString());
    }

    if (!Support)
    {
        if (GraphOwner->StaticClass()->ImplementsInterface(UYetAnotherGraphInterface::StaticClass()))
            Support = GraphOwner;
        else
            WLog("The object %s does not implement the graph interface.", *GraphOwner->StaticClass()->GetDisplayNameText().ToString());
    }

    IYetAnotherGraphInterface* Interface = Cast<IYetAnotherGraphInterface>(Support);
    if (Interface)
        Integer = Interface->GetIntegerVariable(IndexName, Result);
    if (!Result)
        ELog("%s:Error upon looking for an integer", *StaticClass()->GetDisplayNameText().ToString());

   
    return Integer;
}

#undef LOCTEXT_NAMESPACE
