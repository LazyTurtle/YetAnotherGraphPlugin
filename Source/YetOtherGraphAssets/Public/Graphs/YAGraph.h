// Copyright (c) 2018 Jhonny Hueller
#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "SubclassOf.h"
#include "Logger.h"
#include "YAGraph.generated.h"

#define LOCTEXT_NAMESPACE "UYAGraph"

class UYANode;
class UStartNode;

/**
 * 
 */
UCLASS(Blueprintable,BlueprintType)
class YETOTHERGRAPHASSETS_API UYAGraph : public UObject
{
	GENERATED_BODY()
	
public:
	UYAGraph();

	UPROPERTY(BlueprintReadOnly, Category = "Graph Data")
		TArray<UYANode*>Nodes;

	UPROPERTY(BlueprintReadOnly, Category = "Graph Data")
		TMap<FString, UYANode*>NamedNodes;

    UPROPERTY(BlueprintReadOnly, Category = "Graph Data")
        TMap<UYANode*, FString>NodesNames;

    UPROPERTY(BlueprintReadWrite, Category = "Graph Data")
        UObject* Owner;

	UFUNCTION(BlueprintPure, Category = "Graph Data")
		TArray<UStartNode*> GetStartingNodes();

    UFUNCTION(BlueprintCallable, Category = "Graph Data")
        void InitGraph(UObject* ParentObject);



#if WITH_EDITORONLY_DATA

public:

	UPROPERTY()
	class UEdGraph* EdGraph;

	template <class T>
	T* SpawnNodeInsideGraph(TSubclassOf<UYANode> InNodeClass)
	{
		T* SpawenNode = NewObject<T>(this, InNodeClass, NAME_None, RF_Transactional);
		AddNode(SpawenNode);
		return SpawenNode;
	}


	virtual void AddNode(UYANode* InNode);
	virtual void RemoveNode(UYANode* NodeToRemove);

#endif
};

#undef LOCTEXT_NAMESPACE