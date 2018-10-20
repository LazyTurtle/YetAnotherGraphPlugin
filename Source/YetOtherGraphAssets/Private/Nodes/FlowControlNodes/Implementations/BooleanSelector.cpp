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

    if (GraphOwner->StaticClass()->ImplementsInterface(UGraphSupportComponent::StaticClass()))
    {
        IGraphSupportComponentInterface* Interface = Cast<IGraphSupportComponentInterface>(GraphOwner);
        Support = Interface->GetGraphSupportComponent();
    }
    else
    {
        WLog("The object %s does not implement the graph support component interface.", *GraphOwner->StaticClass()->GetDisplayNameText().ToString());
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
        Result = Interface->GetBooleanVariable(Name);

    return Result;
}

#undef LOCTEXT_NAMESPACE
