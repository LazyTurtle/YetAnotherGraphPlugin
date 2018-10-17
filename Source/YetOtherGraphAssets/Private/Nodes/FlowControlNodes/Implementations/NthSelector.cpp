// Copyright (c) 2018 Jhonny Hueller

#include "NthSelector.h"
#include "YAGraph.h"
#include "Logger.h"
#include "YetAnotherGraphInterface.h"

#define LOCTEXT_NAMESPACE "NthSelector"

UNthSelector::UNthSelector()
{
    DefaultNodeTitle= LOCTEXT("NthSelector", "'Nth Selector");
}

int32 UNthSelector::IndexEvaluation_Implementation(UObject* GraphOwner)
{
    int32 Result = 0;
    if (GraphOwner->StaticClass()->ImplementsInterface(UYetAnotherGraphInterface::StaticClass()))
    {
        IYetAnotherGraphInterface* Interface = Cast<IYetAnotherGraphInterface>(GraphOwner);
        if (Interface)
            Result = Interface->GetIntegerVariable(IndexName);
    }
    else
    {
        ELog("The object %s does not implement the graph interface.", *GraphOwner->StaticClass()->GetDisplayNameText().ToString());
    }
   
    return Result;
}

#undef LOCTEXT_NAMESPACE
