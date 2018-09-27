#include "YetAnotherAssetFactory.h"
#include "YAGraph.h"

UYetAnotherAssetFactory::UYetAnotherAssetFactory()
{
	SupportedClass = UYAGraph::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UYetAnotherAssetFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UYAGraph>(InParent, InClass, InName, Flags);
}