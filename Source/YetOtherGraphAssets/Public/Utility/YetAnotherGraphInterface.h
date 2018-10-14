// Copyright (c) 2018 Jhonny Hueller

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "YetAnotherGraphInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UYetAnotherGraphInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * This interface is used to exchange informations between Graphs. used mostly on dynamic nodes to avoid having to create new child blueprints or new c++ classes just for simple checks
 */
class YETOTHERGRAPHASSETS_API IYetAnotherGraphInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	
    UFUNCTION(BlueprintNativeEvent, Category = "Graph interface");
    void SetBooleanVariable(FName BooleanName);

    UFUNCTION(BlueprintNativeEvent, Category = "Graph interface");
    bool GetBooleanVariable(FName BooleanName) const;

    UFUNCTION(BlueprintNativeEvent, Category = "Graph interface");
    void SetIntegerVariable(FName IntegerName, int32 Value);

    UFUNCTION(BlueprintNativeEvent, Category = "Graph interface");
    int32 GetIntegerVariable(FName IntegerName) const;



};
