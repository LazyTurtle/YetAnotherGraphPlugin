

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "YAEdGraph.generated.h"

/**
 * 
 */
UCLASS()
class UYAEdGraph : public UEdGraph
{
	GENERATED_UCLASS_BODY()
	
public:

	virtual bool IsNameUnique(const FText& InName);
	virtual void ClearOldLinks();
	virtual void LinkAssetNodes();
	
};
