#pragma once

#include "CoreMinimal.h"
#include "SGraphNode.h"
#include "NotifyHook.h"
#include "IDetailsView.h"

/**
 * 
 */
class SYAGraphNode : public SGraphNode, public FNotifyHook
{
public:
	SLATE_BEGIN_ARGS(SYAGraphNode) {}
	SLATE_END_ARGS()

	// Inherited via SGraphNode
	void Construct(const FArguments& InArgs, UEdGraphNode* InNode);
	void UpdateGraphNode() override;
	void CreatePinWidgets() override;
	void AddPin(const TSharedRef<SGraphPin>& PinToAdd) override;
	bool IsNameReadOnly() const override;
	void OnNameTextCommited(const FText& InText, ETextCommit::Type CommitInfo);

protected:

	TSharedPtr<SVerticalBox> ContentWidget;
	TSharedPtr<SBorder> ErrorBorder;
    TSharedPtr<STextBlock> NodeHeader;

	virtual void CreateContent();
    virtual void CreateHeader();
};
