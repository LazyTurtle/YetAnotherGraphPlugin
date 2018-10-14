// Copyright (c) 2018 Jhonny Hueller
#pragma once

#include "CoreMinimal.h"
#include "SGraphPin.h"

#define LOCTEXT_NAMESPACE "SYetAnotherGraphPin"

/**
 * 
 */
class SYetAnotherGraphPin : public SGraphPin
{
public:
	void Construct(const FArguments& InArgs, UEdGraphPin* InPin);
	virtual TSharedRef<SWidget>	GetDefaultValueWidget() override;
};

#undef LOCTEXT_NAMESPACE