// Copyright (c) 2018 Jhonny Hueller

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "YetAnotherGraphInterface.h"
#include "GraphSupportComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class YETOTHERGRAPHASSETS_API UGraphSupportComponent : public UActorComponent, public IYetAnotherGraphInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGraphSupportComponent();

    /*UFUNCTION(BlueprintNativeEvent, Category = "Graph Support")
        void SetNamedBoolean(FName VariableName, bool Value);
        virtual void SetNamedBoolean_Implementation(FName VariableName, bool Value);

    UFUNCTION(BlueprintNativeEvent, Category = "Graph Support")
        void SetNamedInteger(FName VariableName, int32 Value);
        virtual void SetNamedInteger_Implementation(FName VariableName, bool Value);*/


    // Inherited from YetAnotherGraphInterface
    bool SetBooleanVariable_Implementation(FName BooleanName, bool Value) override;
    bool GetBooleanVariable_Implementation(FName BooleanName) const override;
    bool SetIntegerVariable_Implementation(FName IntegerName, int32 Value) override;
    int32 GetIntegerVariable_Implementation(FName IntegerName, bool& Result) const override;

    UPROPERTY(BlueprintReadOnly, Category = "Graph Support")
        TMap<FName, bool>NamedBooleans;

    UPROPERTY(BlueprintReadOnly, Category = "Graph Support")
        TMap<FName, int32>NamedIntegers;

    UPROPERTY()
        AActor* Owner;


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
	
};
