// Copyright (c) 2018 Jhonny Hueller
#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

class FYetAnotherGraphEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual void StartNodeHelper();
	virtual TSharedPtr<struct FYetAnotherNodeClassHelper> GetHelper() { return NodeHelper; }

private:
	TSharedPtr<struct FYetAnotherNodeClassHelper>NodeHelper;
};
