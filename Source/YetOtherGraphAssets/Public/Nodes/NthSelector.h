// Copyright (c) 2018 Jhonny Hueller

#pragma once

#include "CoreMinimal.h"
#include "Nodes/MultiNodeSelector.h"
#include "NthSelector.generated.h"

/**
 * 
 */
UCLASS()
class YETOTHERGRAPHASSETS_API UNthSelector : public UMultiNodeSelector
{
	GENERATED_BODY()
	
public:

    UNthSelector();

    UPROPERTY(EditAnywhere, Category = "Nth Selector")
        FName VariableName;
	
	//Inherited from UMultiNodeSelector
    int32 IndexEvaluation_Implementation() override;

};
