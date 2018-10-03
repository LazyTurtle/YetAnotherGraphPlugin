#include "YAEdGraph.h"
#include "YANode.h"
#include "YetAnotherEdGraphNode.h"
#include "EditorLogger.h"
#include "EdGraph/EdGraphPin.h"

UYAEdGraph::UYAEdGraph(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer){}

bool UYAEdGraph::IsNameUnique(const FText & InName)
{
	bool bUnique = true;
	for (UEdGraphNode* Node : Nodes)
	{
		UYetAnotherEdGraphNode* PNode = Cast<UYetAnotherEdGraphNode>(Node);
		FText NodeName = PNode->GetEdNodeName();
		if (bUnique==true && !NodeName.IsEmpty())
		{
			if (NodeName.EqualToCaseIgnored(InName))
			{
				EDWLog("I found another node with the same name: %s.", *NodeName.ToString());
				bUnique = false;
			}
		}
	}
	return bUnique;
}

void UYAEdGraph::ClearOldLinks()
{
	for (UEdGraphNode* EditorNode : Nodes)
	{
		UYetAnotherEdGraphNode* EdNode = Cast<UYetAnotherEdGraphNode>(EditorNode);
		if (EdNode)
			EdNode->AssetNode->ClearLinks();
	}
}

void UYAEdGraph::LinkAssetNodes()
{
	ClearOldLinks();
	EDLLog("Starting to link all asset nodes from the editor graph links.");
	for (UEdGraphNode* EditorNode : Nodes)
	{
		if (UYetAnotherEdGraphNode* EdNode = Cast<UYetAnotherEdGraphNode>(EditorNode))
		{
			UYANode* NodeAsset = EdNode->AssetNode;
			if (NodeAsset != nullptr)
			{
				TArray<UEdGraphPin*>& EdPinsParent = EdNode->Pins;
				
				for (UEdGraphPin* Pin : EdPinsParent)
				{
					//Take only the output pins
					if (Pin->Direction == EEdGraphPinDirection::EGPD_Output)
					{
						TArray<UEdGraphPin*>& EdPinsChildren = Pin->LinkedTo;
						for (UEdGraphPin* LinkedPin : EdPinsChildren)
						{
							UYetAnotherEdGraphNode* Child = Cast<UYetAnotherEdGraphNode>(LinkedPin->GetOwningNode());
							if (Child)
							{
								NodeAsset->LinkArgumentNodeAsChild(Child->AssetNode);
							}
							else
							{
								EDELog("The pin is not linked to anything.");
							}
						}
					}

				}
			}
			else
			{
				EDELog("There is no asset node linked to this editor node.");
			}
		}
		else 
		{
			EDWLog("An unknow EdNode has been found.");
		}
	}

}

void UYAEdGraph::RefreshNodes()
{
	for (UEdGraphNode* Node : Nodes)
	{
		if (UYetAnotherEdGraphNode* YANode = Cast<UYetAnotherEdGraphNode>(Node))
			YANode->UpdateVisualNode();
	}
}
