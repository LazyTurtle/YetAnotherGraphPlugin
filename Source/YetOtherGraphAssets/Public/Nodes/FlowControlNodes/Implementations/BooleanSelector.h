// Copyright (c) 2018 Jhonny Hueller

#pragma once

#include "CoreMinimal.h"
#include "BinarySelectNode.h"
#include "BooleanSelector.generated.h"

/**
 * 
 */
UCLASS(meta = (Category = "FlowControl"))
class YETOTHERGRAPHASSETS_API UBooleanSelector : public UBinarySelectNode
{
    GENERATED_BODY()

public:

    UBooleanSelector();

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Boolean Selector")
    FName Name;
	
	//Inherited from BinarySelectNode
    bool BooleanEvaluation_Implementation(UObject* GraphOwner) override;
	
};
