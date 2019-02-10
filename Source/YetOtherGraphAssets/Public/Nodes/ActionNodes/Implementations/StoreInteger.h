// Copyright (c) 2018 Jhonny Hueller

#pragma once

#include "CoreMinimal.h"
#include "ActionNode.h"
#include "StoreInteger.generated.h"

/**
 * 
 */
UCLASS(meta = (Category = "ActionNodes"))
class YETOTHERGRAPHASSETS_API UStoreInteger : public UActionNode
{
	GENERATED_BODY()
	
public:
    UStoreInteger();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Informations")
        FName Name;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Informations")
        int32 Value;
	
    //Inherited from UActionNode
    void ActionToPerform_Implementation(UObject* GraphOwner) override;
	
};
