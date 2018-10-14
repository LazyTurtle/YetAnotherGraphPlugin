// Copyright (c) 2018 Jhonny Hueller


#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "YAEdGraph.generated.h"

/**
 * 
 */
class UYAGraph;

UCLASS()
class UYAEdGraph : public UEdGraph
{
	GENERATED_BODY()
	
public:

	virtual bool IsNameUnique(const FText& InName);
	virtual void SaveGraph();
	virtual void ClearOldLinks();
	virtual void LinkAssetNodes();
	virtual void RefreshNodes();
	virtual void MapNamedNodes();
	virtual UYAGraph* GetGraphAsset();
};
