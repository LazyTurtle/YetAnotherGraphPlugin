#include "YetAnotherEdGraphNode.h"
#include "YANode.h"
#include "YAGraph.h"
#include "YAEdGraph.h"
#include "SYAGraphNode.h"
#include "IDetailsView.h"
#include "PropertyEditorModule.h"
#include "ModuleManager.h"

#define LOCTEXT_NAMESPACE "YetAnotherEdGraphNode"

UYetAnotherEdGraphNode::UYetAnotherEdGraphNode(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer){}


TSharedPtr<SGraphNode> UYetAnotherEdGraphNode::CreateVisualWidget()
{
	SlateNode= SNew(SYAGraphNode, this);
	return SlateNode;
}

TSharedPtr<SWidget> UYetAnotherEdGraphNode::GetContentWidget()
{
	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.bAllowSearch = false;
	DetailsViewArgs.bLockable = false;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	TSharedPtr<IDetailsView> View = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	View->SetObject(AssetNode);
	return View;
}

void UYetAnotherEdGraphNode::UpdateVisualNode()
{
	SlateNode->UpdateGraphNode();
}

bool UYetAnotherEdGraphNode::HasOutputPins()
{
	return AssetNode ? AssetNode->HasOutputPins() : true;
}

bool UYetAnotherEdGraphNode::HasInputPins()
{
	return AssetNode ? AssetNode->HasInputPins() : true;
}

void UYetAnotherEdGraphNode::AllocateDefaultPins()
{
	UEdGraphNode::AllocateDefaultPins();
	if (HasInputPins())
		CreatePin(EGPD_Input, FName("InCategory"), FName("InPinName"));
	if (HasOutputPins())
		CreatePin(EGPD_Output, FName("OutCategory"), FName("OutPinName"));
}

FText UYetAnotherEdGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
    switch (TitleType)
    {
    case ENodeTitleType::Type::MenuTitle:
        return AssetNode->GetNodeTitle();
    default:
        FText Title = GetEdNodeName();
        return Title.IsEmpty() ? AssetNode->GetNodeTitle() : Title;
    }
}

void UYetAnotherEdGraphNode::PrepareForCopying()
{
	if (AssetNode)
		AssetNode->Rename(nullptr, this, REN_DontCreateRedirectors | REN_DoNotDirty);
	UEdGraphNode::PrepareForCopying();
}

void UYetAnotherEdGraphNode::DestroyNode()
{
	if (AssetNode)
	{
		AssetNode->GetGraph()->RemoveNode(AssetNode);
		AssetNode->ConditionalBeginDestroy();
		AssetNode = nullptr;
	}
	UEdGraphNode::DestroyNode();
}

void UYetAnotherEdGraphNode::AutowireNewNode(UEdGraphPin * FromPin)
{
	if (FromPin)
	{
		UEdGraphNode::AutowireNewNode(FromPin);
		if (FromPin->Direction == EEdGraphPinDirection::EGPD_Input)
		{
			if (GetSchema()->TryCreateConnection(FromPin, FindPin(FName("OutPinName"))))
			{
				FromPin->GetOwningNode()->NodeConnectionListChanged();
			}
		}
		if (FromPin->Direction == EEdGraphPinDirection::EGPD_Output)
		{
			if (GetSchema()->TryCreateConnection(FromPin, FindPin(FName("InPinName"))))
			{
				FromPin->GetOwningNode()->NodeConnectionListChanged();
			}
		}
	}
}

void UYetAnotherEdGraphNode::SetAssetNode(UYANode * InNode)
{
	AssetNode = InNode;
}

UYANode * UYetAnotherEdGraphNode::GetAssetNode()
{
	return AssetNode;
}

void UYetAnotherEdGraphNode::PostCopyNode()
{
	if (AssetNode)
	{
		UEdGraph* EdGraph = GetGraph();
		UObject* ParentAsset = EdGraph ? EdGraph->GetOuter() : nullptr;
		AssetNode->Rename(nullptr, ParentAsset, REN_DontCreateRedirectors | REN_DoNotDirty);
		AssetNode->ClearFlags(RF_Transient);
	}
}

bool UYetAnotherEdGraphNode::RenameUniqueNode(const FText & NewName)
{
	bool bRenamedNode = false;

	UYAEdGraph* EdGraph = Cast<UYAEdGraph>(GetGraph());

	if (EdGraph->IsNameUnique(NewName))
	{
		Modify();
		SetEdNodeName(NewName);
		bRenamedNode = true;
	}
	return bRenamedNode;
}
FText UYetAnotherEdGraphNode::GetEdNodeName() const
{
	return EdNodeName;
}
void UYetAnotherEdGraphNode::SetEdNodeName(const FText & Name)
{
	EdNodeName = Name;
}

void UYetAnotherEdGraphNode::SetEdNodeName(const FName & Name)
{
	SetEdNodeName(FText::FromName(Name));
}


#undef LOCTEXT_NAMESPACE