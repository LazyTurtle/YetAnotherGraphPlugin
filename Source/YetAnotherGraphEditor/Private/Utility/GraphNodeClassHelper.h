#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "UObject/WeakObjectPtr.h"
#include "GraphNodeClassHelper.generated.h"

/**
 * 
 */

USTRUCT()
struct FYetAnotherNodeClassData
{
	GENERATED_USTRUCT_BODY()

	FYetAnotherNodeClassData() {}
	FYetAnotherNodeClassData(UClass* InClass, const FString& InDeprecatedMessage);
	FYetAnotherNodeClassData(const FString& InAssetName, const FString& InGeneratedClassPackage, const FString& InClassName, UClass* InClass);

	FString ToString() const;
	FString GetClassName() const;
	FText GetCategory() const;
	FString GetDisplayName() const;
	UClass* GetClass(bool bSilent = false);
	bool IsAbstract() const;

	FORCEINLINE bool IsBlueprint() const { return AssetName.Len() > 0; }
	FORCEINLINE bool IsDeprecated() const { return DeprecatedMessage.Len() > 0; }
	FORCEINLINE FString GetDeprecatedMessage() const { return DeprecatedMessage; }
	FORCEINLINE FString GetPackageName() const { return GeneratedClassPackage; }

	/** set when child class masked this one out (e.g. always use game specific class instead of engine one) */
	uint32 bIsHidden : 1;

	/** set when class wants to hide parent class from selection (just one class up hierarchy) */
	uint32 bHideParent : 1;

private:

	/** pointer to uclass */
	TWeakObjectPtr<UClass> Class;

	/** path to class if it's not loaded yet */
	UPROPERTY()
		FString AssetName;

	UPROPERTY()
		FString GeneratedClassPackage;

	/** resolved name of class from asset data */
	UPROPERTY()
		FString ClassName;

	/** User-defined category for this class */
	UPROPERTY()
		FText Category;

	/** message for deprecated class */
	FString DeprecatedMessage;
};

struct FYetAnotherNodeClassNode
{
	FYetAnotherNodeClassData Data;
	FString ParentClassName;

	TSharedPtr<FYetAnotherNodeClassNode> ParentNode;
	TArray<TSharedPtr<FYetAnotherNodeClassNode> > SubNodes;

	void AddUniqueSubNode(TSharedPtr<FYetAnotherNodeClassNode> SubNode);
};

struct FYetAnotherNodeClassHelper
{
public:
	DECLARE_MULTICAST_DELEGATE(FOnPackageListUpdated);

	FYetAnotherNodeClassHelper(UClass* InRootClass);
	~FYetAnotherNodeClassHelper();

	void GatherClasses(const UClass* BaseClass, TArray<FYetAnotherNodeClassData>& AvailableClasses);
	static FString GetDeprecationMessage(const UClass* Class);

	void OnAssetAdded(const struct FAssetData& AssetData);
	void OnAssetRemoved(const struct FAssetData& AssetData);
	void InvalidateCache();
	void OnHotReload(bool bWasTriggeredAutomatically);

	static void AddUnknownClass(const FYetAnotherNodeClassData& ClassData);
	static bool IsClassKnown(const FYetAnotherNodeClassData& ClassData);
	static FOnPackageListUpdated OnPackageListUpdated;

	static int32 GetObservedBlueprintClassCount(UClass* BaseNativeClass);
	static void AddObservedBlueprintClasses(UClass* BaseNativeClass);
	void UpdateAvailableBlueprintClasses();

private:

	UClass* RootNodeClass;
	TSharedPtr<FYetAnotherNodeClassNode> RootNode;
	static TArray<FName> UnknownPackages;
	static TMap<UClass*, int32> BlueprintClassCount;

	TSharedPtr<FYetAnotherNodeClassNode> CreateClassDataNode(const struct FAssetData& AssetData);
	TSharedPtr<FYetAnotherNodeClassNode> FindBaseClassNode(TSharedPtr<FYetAnotherNodeClassNode> Node, const FString& ClassName);
	void FindAllSubClasses(TSharedPtr<FYetAnotherNodeClassNode> Node, TArray<FYetAnotherNodeClassData>& AvailableClasses);

	UClass* FindAssetClass(const FString& GeneratedClassPackage, const FString& AssetName);
	void BuildClassGraph();
	void AddClassGraphChildren(TSharedPtr<FYetAnotherNodeClassNode> Node, TArray<TSharedPtr<FYetAnotherNodeClassNode> >& NodeList);

	bool IsHidingClass(UClass* Class);
	bool IsHidingParentClass(UClass* Class);
	bool IsPackageSaved(FName PackageName);
};