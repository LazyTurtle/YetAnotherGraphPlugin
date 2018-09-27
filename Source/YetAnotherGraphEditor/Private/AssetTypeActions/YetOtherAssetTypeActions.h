

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"

/**
 * 
 */
class FYetOtherAssetTypeActions : public FAssetTypeActions_Base
{
public:
	FYetOtherAssetTypeActions();

	// Inherited via FAssetTypeActions_Base
	virtual FText GetName() const override;
	virtual UClass * GetSupportedClass() const override;
	virtual FColor GetTypeColor() const override;
	virtual uint32 GetCategories() override;
	virtual bool HasActions(const TArray<UObject*>& InObjects) const override;
	virtual void OpenAssetEditor(const TArray<UObject*>& InObjects, TSharedPtr<class IToolkitHost> EditWithinLevelEditor = TSharedPtr<IToolkitHost>()) override;

};
