// Copyright (c) 2018 Jhonny Hueller

#include "StoreBoolean.h"
#include "YetAnotherGraphInterface.h"

#define LOCTEXT_NAMESPACE "StoreBoolean"

UStoreBoolean::UStoreBoolean()
{
    DefaultNodeTitle= LOCTEXT("StoreBoolean", "Store Boolean");
}
void UStoreBoolean::ActionToPerform_Implementation(UObject * GraphOwner)
{
    if (Name.IsValid())
    {
        if (GraphOwner->StaticClass()->ImplementsInterface(UYetAnotherGraphInterface::StaticClass()))
        {
            IYetAnotherGraphInterface* Interface = Cast<IYetAnotherGraphInterface>(GraphOwner);
            if (Interface)
                Interface->SetBooleanVariable(Name,Value);
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
