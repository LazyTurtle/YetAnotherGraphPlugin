#include "SYAGraphNode.h"
#include "Slate.h"
#include "YetAnotherEdGraphNode.h"
#include "SGraphPin.h"
#include "SYetAnotherGraphPin.h"

#define LOCTEXT_NAMESPACE "SYAGraphNode"

void SYAGraphNode::Construct(const FArguments & InArgs, UEdGraphNode * InNode)
{
	GraphNode = InNode;

	UpdateGraphNode();
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SYAGraphNode::UpdateGraphNode()
{

	const FMargin NodePadding = FMargin(2.0f);

	InputPins.Empty();
	OutputPins.Empty();

	RightNodeBox.Reset();
	LeftNodeBox.Reset();

	TSharedPtr<SNodeTitle> NodeTitle = SNew(SNodeTitle, GraphNode);

	this->ContentScale.Bind(this, &SGraphNode::GetContentScale);

	this->GetOrAddSlot(ENodeZone::Center)
		.HAlign(HAlign_Fill)
		.VAlign(VAlign_Center)
		[
			SNew(SBorder)
			.BorderImage(FEditorStyle::GetBrush("Graph.StateNode.Body"))
		.Padding(FMargin(10.0f))
		.BorderBackgroundColor(FLinearColor(0.1f, 0.1f, 0.1f))
		[
			SNew(SVerticalBox)

			+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SBox)
			[
				SAssignNew(LeftNodeBox, SVerticalBox)
			]
		]
	+ SVerticalBox::Slot()
		.HAlign(HAlign_Center)
		.AutoHeight()
		[
			SAssignNew(InlineEditableText, SInlineEditableTextBlock)
			.Style(FEditorStyle::Get(), "Graph.StateNode.NodeTitleInlineEditableText")
		.Text(NodeTitle.Get(), &SNodeTitle::GetHeadTitle)
		.IsReadOnly(this, &SYAGraphNode::IsNameReadOnly)
		.OnTextCommitted(this, &SYAGraphNode::OnNameTextCommited)
		.OnVerifyTextChanged(this, &SYAGraphNode::OnVerifyNameTextChanged)
		]
	+ SVerticalBox::Slot()
		.AutoHeight()
		[
			NodeTitle.ToSharedRef()
		]
	+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SAssignNew(ContentWidget, SVerticalBox)
		]
	+ SVerticalBox::Slot()
		.AutoHeight()
		[
			SNew(SBox)
			[
				SAssignNew(RightNodeBox, SVerticalBox)
			]
		]
		]
		];

	CreatePinWidgets();
	CreateContent();
}

void SYAGraphNode::CreatePinWidgets()
{
	UYetAnotherEdGraphNode* EdNode = CastChecked<UYetAnotherEdGraphNode>(GraphNode);
	for (int32 i = 0; i < EdNode->Pins.Num(); ++i)
	{
		UEdGraphPin* Pin = EdNode->Pins[i];
		if (!Pin->bHidden)
		{
			TSharedPtr<SGraphPin>NewPin = SNew(SYetAnotherGraphPin, Pin);
			AddPin(NewPin.ToSharedRef());
		}
	}
}

void SYAGraphNode::AddPin(const TSharedRef<SGraphPin>& PinToAdd)
{
	PinToAdd->SetOwner(SharedThis(this));
	if (PinToAdd->GetDirection() == EEdGraphPinDirection::EGPD_Input)
	{
		LeftNodeBox->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.FillHeight(1.0f)
			.Padding(20.0f, 0.0f)
			[
				PinToAdd
			];
		InputPins.Add(PinToAdd);
	}
	else if (PinToAdd->GetDirection() == EEdGraphPinDirection::EGPD_Output)
	{
		RightNodeBox->AddSlot()
			.HAlign(HAlign_Fill)
			.VAlign(VAlign_Fill)
			.FillHeight(1.0f)
			.Padding(20.0f, 0.0f)
			[
				PinToAdd
			];
		OutputPins.Add(PinToAdd);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No direction found"));
	}
}

bool SYAGraphNode::IsNameReadOnly() const
{
	return false;
}

void SYAGraphNode::OnNameTextCommited(const FText & InText, ETextCommit::Type CommitInfo)
{
	UYetAnotherEdGraphNode* UEdNode = CastChecked<UYetAnotherEdGraphNode>(GraphNode);

	if (UEdNode)
		if (UEdNode->RenameUniqueNode(InText))
		{
			UpdateGraphNode();
			SGraphNode::OnNameTextCommited(InText, CommitInfo);
		}

}
void SYAGraphNode::CreateContent()
{
	UYetAnotherEdGraphNode* Node = Cast<UYetAnotherEdGraphNode>(GraphNode);

	ContentWidget->AddSlot()
		[
			Node->GetContentWidget().ToSharedRef()
		];
}
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
#undef LOCTEXT_NAMESPACE