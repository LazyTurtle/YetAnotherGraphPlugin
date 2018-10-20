// Copyright (c) 2018 Jhonny Hueller

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "YetAnotherGraphInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(Blueprintable)
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
	
    // The boolean returns shouldn't be used and they're here only to aggregate all the functions under the "Intefaces" section of blueprints


    UFUNCTION(BlueprintNativeEvent, Category = "Graph interface")
    bool SetBooleanVariable(FName BooleanName,bool Value); // unused return
    virtual bool SetBooleanVariable_Implementation(FName BooleanName, bool Value) { return false; }

    UFUNCTION(BlueprintNativeEvent, Category = "Graph interface")
    bool GetBooleanVariable(FName BooleanName) const;
    virtual bool GetBooleanVariable_Implementation(FName BooleanName) const { return false; }

    UFUNCTION(BlueprintNativeEvent, Category = "Graph interface")
    bool SetIntegerVariable(FName IntegerName, int32 Value); // unused return
    virtual bool SetIntegerVariable_Implementation(FName IntegerName, int32 Value) { return false; }

    UFUNCTION(BlueprintNativeEvent, Category = "Graph interface")
    int32 GetIntegerVariable(FName IntegerName, bool& Result) const;
    virtual int32 GetIntegerVariable_Implementation(FName IntegerName,bool& Result) const { return 0; }



};
