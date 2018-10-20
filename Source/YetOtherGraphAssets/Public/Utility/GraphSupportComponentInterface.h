// Copyright (c) 2018 Jhonny Hueller

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GraphSupportComponent.h"
#include "GraphSupportComponentInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGraphSupportComponentInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class YETOTHERGRAPHASSETS_API IGraphSupportComponentInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
    UFUNCTION(BlueprintNativeEvent, Category = "Graph Support Interface")
        UGraphSupportComponent* GetGraphSupportComponent();
    virtual UGraphSupportComponent* GetGraphSupportComponent_Implementation() = 0;
	
};
