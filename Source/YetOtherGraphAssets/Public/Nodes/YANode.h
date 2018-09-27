#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "YANode.generated.h"

#define LOCTEXT_NAMESPACE "UYANode"

class UYAGraph;
/**
 * 
 */
UCLASS(Abstract, Blueprintable, BlueprintType)
class YETOTHERGRAPHASSETS_API UYANode : public UObject
{
	GENERATED_BODY()
	
public:
	UYANode();

	
	UFUNCTION(BlueprintPure)
		TArray<UYANode*> GetChildren();
	UFUNCTION(BlueprintPure)
		TArray<UYANode*> GetParents();
	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
		FText InternalGetNodeTitle();
	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
		bool HasInputPins();
	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
		bool HasOutputPins();


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
	virtual FText GetNodeTitle();

protected:
	UPROPERTY()
		UYAGraph * Graph = nullptr;
	UPROPERTY()
		TArray<UYANode*> ParentNodes;
	UPROPERTY()
		TArray<UYANode*> ChildNodes;

	bool bHasInputPins = true;
	bool bHasOutputPins = true;
	FText DefaultNodeTitle = FText();
};

#undef LOCTEXT_NAMESPACE