// Copyright (c) 2018 Jhonny Hueller

#include "StoreInteger.h"
#include "YetAnotherGraphInterface.h"

#define LOCTEXT_NAMESPACE "StoreInteger"

UStoreInteger::UStoreInteger()
{
    DefaultNodeTitle= LOCTEXT("StoreInteger", "Store Integer");
}
void UStoreInteger::ActionToPerform_Implementation(UObject * GraphOwner)
{
    if (Name.IsValid())
    {
        if (GraphOwner->StaticClass()->ImplementsInterface(UYetAnotherGraphInterface::StaticClass()))
        {
            IYetAnotherGraphInterface* Interface = Cast<IYetAnotherGraphInterface>(GraphOwner);
            if (Interface)
                Interface->SetIntegerVariable(Name,Value);
        }
        else
        {
            ELog("The object %s does not implement the graph interface.", *GraphOwner->StaticClass()->GetDisplayNameText().ToString());
        }
    }
    else
    {
        ELog("The variable name isn't valid.");
    }
}

#undef LOCTEXT_NAMESPACE