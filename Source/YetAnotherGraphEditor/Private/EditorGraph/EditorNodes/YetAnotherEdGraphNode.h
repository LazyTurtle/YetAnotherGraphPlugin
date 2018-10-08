

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphNode.h"
#include "YANode.h"
#include "SubclassOf.h"
#include "YetAnotherEdGraphNode.generated.h"

/**
 * 
 */
UCLASS()
class UYetAnotherEdGraphNode : public UEdGraphNode
{
	GENERATED_UCLASS_BODY()
	
public:

	// Inherited via EdGraphNode.h
	TSharedPtr<SGraphNode> CreateVisualWidget() override; 	/** Create a visual widget to represent this node in a graph editor or graph panel.  If not implemented, the default node factory will be used. */
	virtual void AllocateDefaultPins() override;
	FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual void PrepareForCopying() override;
	virtual void DestroyNode() override;
	virtual void AutowireNewNode(UEdGraphPin* FromPin) override;


	virtual void SetAssetNode(UYANode* InNode);
	virtual UYANode* GetAssetNode();

	virtual void PostCopyNode();

	virtual bool RenameUniqueNode(const FText& NewName);

	virtual FText GetEdNodeName() const;
	virtual void SetEdNodeName(const FText& Name);
	virtual void SetEdNodeName(const FName& Name);

	virtual TSharedPtr<SWidget> GetContentWidget();

	virtual void UpdateVisualNode();

protected:

	virtual bool HasOutputPins();
	virtual bool HasInputPins();
	TSharedPtr<SGraphNode>SlateNode;

public:

	UPROPERTY(Instanced)
		UYANode* AssetNode = nullptr;

private:
	UPROPERTY()
		FText EdNodeName;

};
