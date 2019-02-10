// Copyright (c) 2018 Jhonny Hueller

#pragma once

#include "CoreMinimal.h"
#include "MultiNodeSelector.h"
#include "NthSelector.generated.h"

/**
 * 
 */
UCLASS(meta = (Category = "FlowControl"))
class YETOTHERGRAPHASSETS_API UNthSelector : public UMultiNodeSelector
{
	GENERATED_BODY()
	
public:

    UNthSelector();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nth Selector")
        FName IndexName;
	
	//Inherited from UMultiNodeSelector
    int32 IndexEvaluation_Implementation(UObject* GraphOwner) override;

};
