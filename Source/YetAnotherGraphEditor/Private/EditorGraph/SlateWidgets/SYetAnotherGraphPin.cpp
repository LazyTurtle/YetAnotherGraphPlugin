#include "SYetAnotherGraphPin.h"

void SYetAnotherGraphPin::Construct(const FArguments & InArgs, UEdGraphPin * InPin)
{
	this->SetCursor(EMouseCursor::Default);

	bShowLabel = true;

	GraphPinObj = InPin;

	SBorder::FArguments Arguments;
	Arguments.OnMouseButtonDown(this, &SYetAnotherGraphPin::OnPinMouseDown);
	Arguments.Cursor(this, &SYetAnotherGraphPin::GetPinCursor);
	Arguments.Padding(FMargin(10.0f));

	SBorder::Construct(Arguments);
}

TSharedRef<SWidget>	SYetAnotherGraphPin::GetDefaultValueWidget()
{
	return SNew(STextBlock);
}