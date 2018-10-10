#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "YANode.generated.h"

#define LOCTEXT_NAMESPACE "UYANode"

class UYAGraph;
/**
 * Base abstract class for every node of the graph.
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class YETOTHERGRAPHASSETS_API UYANode : public UObject
{
	GENERATED_BODY()
	
public:
	UYANode();

	
	UFUNCTION(BlueprintPure, Category = "Node Data")
		TArray<UYANode*> GetChildren();

	UFUNCTION(BlueprintPure, Category = "Node Data")
		TArray<UYANode*> GetParents();

    UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "Node Data")
	    FText GetNodeTitle();
        virtual FText GetNodeTitle_Implementation();

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "Node Data")
		bool HasInputPins();

	UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "Node Data")
		bool HasOutputPins();

	UFUNCTION(BlueprintNativeEvent, Category = "Node Data")
		UYANode* GetNodePointer();
        virtual UYANode* GetNodePointer_Implementation();

    UFUNCTION(BlueprintNativeEvent, BlueprintPure, Category = "Node Data")
        FText GetCategory();
        virtual FText GetCategory_Implementation();


	virtual void SetGraph(UYAGraph* InGraph);
	virtual UYAGraph* GetGraph();
	virtual void AddToChildren(UYANode* NewChildNode);
	virtual void AddToParent(UYANode* NewParentNode);
	virtual bool HasParentNodes();
	virtual void LinkArgumentNodeAsChild(UYANode* Child);
	virtual void ClearLinks();
	virtual bool RemoveLinkedNode(UYANode* NodeToRemove);
	virtual bool RemoveNodeFromParents(UYANode* NodeToRemove);
	virtual bool RemoveNodeFromChilds(UYANode* NodeToRemove);



protected:
	UPROPERTY()
		UYAGraph * Graph = nullptr;
	UPROPERTY()
		TArray<UYANode*> ParentNodes;
	UPROPERTY()
		TArray<UYANode*> ChildNodes;
    UPROPERTY()
	bool bHasInputPins = true;
    UPROPERTY()
	bool bHasOutputPins = true;
    UPROPERTY()
	FText DefaultNodeTitle = FText();
    UPROPERTY()
    FText Category = FText();


};

#undef LOCTEXT_NAMESPACE