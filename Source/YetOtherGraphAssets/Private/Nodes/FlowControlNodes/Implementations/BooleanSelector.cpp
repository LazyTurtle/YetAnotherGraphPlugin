// Copyright (c) 2018 Jhonny Hueller

#include "BooleanSelector.h"
#include "YAGraph.h"
#include "YetAnotherGraphInterface.h"
#include "Logger.h"
#include "GraphSupportComponent.h"
#include "GraphSupportComponentInterface.h"

#define LOCTEXT_NAMESPACE "BooleanSelector"

UBooleanSelector::UBooleanSelector()
{
    DefaultNodeTitle = LOCTEXT("BooleanSelector", "Boolean Selector");
}

bool UBooleanSelector::BooleanEvaluation_Implementation(UObject* GraphOwner)
{
    bool Result = false;
    UObject* Support = nullptr;

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
            Result = Interface->Execute_GetBooleanVariable(Support, Name);
    }
    else
        ELog("No graph interfaces has been found.");

    
    return Result;
}

#undef LOCTEXT_NAMESPACE
