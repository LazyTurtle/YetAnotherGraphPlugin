// Copyright (c) 2018 Jhonny Hueller

#include "BooleanSelector.h"
#include "YAGraph.h"
#include "YetAnotherGraphInterface.h"
#include "Logger.h"

#define LOCTEXT_NAMESPACE "BooleanSelector"

UBooleanSelector::UBooleanSelector()
{
    DefaultNodeTitle = LOCTEXT("BooleanSelector", "Boolean Selector");
}

bool UBooleanSelector::BooleanEvaluation_Implementation(UObject* GraphOwner)
{
    bool Result = false;
    if (GraphOwner->StaticClass()->ImplementsInterface(UYetAnotherGraphInterface::StaticClass()))
    {
        IYetAnotherGraphInterface* Interface = Cast<IYetAnotherGraphInterface>(GraphOwner);
        if (Interface)
            Result = Interface->GetBooleanVariable(VariableName);
    }
    else
    {
        ELog("The object %s does not implement the graph interface.", *GraphOwner->StaticClass()->GetDisplayNameText().ToString());
    }
    return Result;
}

#undef LOCTEXT_NAMESPACE
