// Copyright (c) 2018 Jhonny Hueller

#include "StoreInteger.h"
#include "YetAnotherGraphInterface.h"
#include "GraphSupportComponent.h"
#include "GraphSupportComponentInterface.h"

#define LOCTEXT_NAMESPACE "StoreInteger"

UStoreInteger::UStoreInteger()
{
    DefaultNodeTitle= LOCTEXT("StoreInteger", "Store Integer");
}
void UStoreInteger::ActionToPerform_Implementation(UObject * GraphOwner)
{
    if (Name.IsValid())
    {
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
                Interface->Execute_SetIntegerVariable(Support, Name, Value);
        }
        else
            ELog("No graph interfaces has been found.");
    }
    else
    {
        ELog("The variable name isn't valid.");
    }
}

#undef LOCTEXT_NAMESPACE