// Copyright (c) 2018 Jhonny Hueller

#pragma once

#include "CoreMinimal.h"
#include "ActionNode.h"
#include "StoreBoolean.generated.h"

/**
 * 
 */
UCLASS(meta = (Category = "ActionNodes"))
class YETOTHERGRAPHASSETS_API UStoreBoolean : public UActionNode
{
	GENERATED_BODY()

public:
    UStoreBoolean();

    UPROPERTY(EditAnywhere, Category = "Informations")
        FName Name;
    UPROPERTY(EditAnywhere, Category = "Informations")
        bool Value;
	
    //Inherited from UActionNode
    void ActionToPerform_Implementation(UObject* GraphOwner) override;
	
};
