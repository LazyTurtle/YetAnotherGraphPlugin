// Copyright (c) 2018 Jhonny Hueller

#pragma once

#include "CoreMinimal.h"
#include "Nodes/BinarySelectNode.h"
#include "BooleanSelector.generated.h"

/**
 * 
 */
UCLASS()
class YETOTHERGRAPHASSETS_API UBooleanSelector : public UBinarySelectNode
{
    GENERATED_BODY()

public:

    UBooleanSelector();

    UPROPERTY(EditAnywhere, Category = "Boolean Selector")
    FName VariableName;
	
	//Inherited from BinarySelectNode
    bool BooleanEvaluation_Implementation(UObject* GraphOwner) override;
	
};
