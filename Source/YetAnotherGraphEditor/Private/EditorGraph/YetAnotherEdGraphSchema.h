

#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraphSchema.h"
#include "YANode.h"
#include "YetAnotherEdGraphSchema.generated.h"

/**
 * 
 */
UCLASS()
class UYetAnotherEdGraphSchema : public UEdGraphSchema
{
	GENERATED_UCLASS_BODY()
	
public:

	/**
	* Get all actions that can be performed when right clicking on a graph or drag-releasing on a graph from a pin
	*
	* @param [in,out]	ContextMenuBuilder	The context (graph, dragged pin, etc...) and output menu builder.
	*/
	void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;

	/**
	* Gets actions that should be added to the right-click context menu for a node or pin
	*
	* @param	CurrentGraph		The current graph.
	* @param	InGraphNode			The node to get the context menu for, if any.
	* @param	InGraphPin			The pin clicked on, if any, to provide additional context
	* @param	MenuBuilder			The menu builder to append actions to.
	* @param	bIsDebugging		Is the graph editor currently part of a debugging session (any non-debugging commands should be disabled)
	*/
	void GetContextMenuActions(const UEdGraph* CurrentGraph, const UEdGraphNode* InGraphNode, const UEdGraphPin* InGraphPin, class FMenuBuilder* MenuBuilder, bool bIsDebugging) const override;

	/**
	* Determine if a connection can be created between two pins.
	*
	* @param	A	The first pin.
	* @param	B	The second pin.
	*
	* @return	An empty string if the connection is legal, otherwise a message describing why the connection would fail.
	*/
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;

	/* returns new FConnectionDrawingPolicy from this schema */
	virtual class FConnectionDrawingPolicy* CreateConnectionDrawingPolicy(int32 InBackLayerID, int32 InFrontLayerID, float InZoomFactor, const FSlateRect& InClippingRect, class FSlateWindowElementList& InDrawElements, class UEdGraph* InGraphObj) const override;

	/**
	* Populate new graph with any default nodes
	*
	* @param	Graph			Graph to add the default nodes to
	* @param	ContextClass	If specified, the graph terminators will use this class to search for context for signatures (i.e. interface functions)
	*/
	virtual void CreateDefaultNodesForGraph(UEdGraph& Graph) const override;

private:
	static void InitNodeClasses();
	static TSet<TSubclassOf<UYANode>> NodeClasses;
};