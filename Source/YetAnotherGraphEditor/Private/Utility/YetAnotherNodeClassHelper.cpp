#include "YetAnotherNodeClassHelper.h"
#include "Class.h"
#include "FeedbackContext.h"
#include "Package.h"
#include "Engine/Blueprint.h"
#include "AssetRegistryModule.h"
#include "HotReloadInterface.h"
#include "Editor.h"
#include "ConstructorHelpers.h"
#include "EditorLogger.h"

#define LOCTEXT_NAMESPACE "YetAnotherNodeClassHelper"


FYetAnotherNodeClassData::FYetAnotherNodeClassData(UClass* InClass, const FString& InDeprecatedMessage) :
	bIsHidden(0),
	bHideParent(0),
	Class(InClass),
	DeprecatedMessage(InDeprecatedMessage)
{
	Category = GetCategory();

	if (InClass)
	{
		ClassName = InClass->GetName();
	}
}

FYetAnotherNodeClassData::FYetAnotherNodeClassData(const FString& InAssetName, const FString& InGeneratedClassPackage, const FString& InClassName, UClass* InClass) :
	bIsHidden(0),
	bHideParent(0),
	Class(InClass),
	AssetName(InAssetName),
	GeneratedClassPackage(InGeneratedClassPackage),
	ClassName(InClassName)
{
	Category = GetCategory();
}

FString FYetAnotherNodeClassData::ToString() const
{
	FString ShortName = GetDisplayName();
	if (!ShortName.IsEmpty())
	{
		return ShortName;
	}

	UClass* MyClass = Class.Get();
	if (MyClass)
	{
		FString ClassDesc = MyClass->GetName();

		if (MyClass->HasAnyClassFlags(CLASS_CompiledFromBlueprint))
		{
			return ClassDesc.LeftChop(2);
		}

		const int32 ShortNameIdx = ClassDesc.Find(TEXT("_"));
		if (ShortNameIdx != INDEX_NONE)
		{
			ClassDesc = ClassDesc.Mid(ShortNameIdx + 1);
		}

		return ClassDesc;
	}

	return AssetName;
}

FString FYetAnotherNodeClassData::GetClassName() const
{
	return Class.IsValid() ? Class->GetName() : ClassName;
}

FString FYetAnotherNodeClassData::GetDisplayName() const
{
	return Class.IsValid() ? Class->GetMetaData(TEXT("DisplayName")) : FString();
}

FText FYetAnotherNodeClassData::GetCategory() const
{
	return Class.IsValid() ? Class->GetMetaDataText(TEXT("Category"), TEXT("UObjectCategory"), Class->GetFullGroupName(false)) : Category;
}

bool FYetAnotherNodeClassData::IsAbstract() const
{
	return Class.IsValid() ? Class.Get()->HasAnyClassFlags(CLASS_Abstract) : false;
}

UClass* FYetAnotherNodeClassData::GetClass(bool bSilent)
{
	UClass* RetClass = Class.Get();
	if (RetClass == NULL && GeneratedClassPackage.Len())
	{
		GWarn->BeginSlowTask(LOCTEXT("LoadPackage", "Loading Package..."), true);

		UPackage* Package = LoadPackage(NULL, *GeneratedClassPackage, LOAD_NoRedirects);
		if (Package)
		{
			Package->FullyLoad();

			UObject* Object = FindObject<UObject>(Package, *AssetName);

			GWarn->EndSlowTask();

			UBlueprint* BlueprintOb = Cast<UBlueprint>(Object);
			RetClass = BlueprintOb ? *BlueprintOb->GeneratedClass :
				Object ? Object->GetClass() :
				NULL;

			Class = RetClass;
		}
	}

	return RetClass;
}

//////////////////////////////////////////////////////////////////////////
TArray<FName> FYetAnotherNodeClassHelper::UnknownPackages;
TMap<UClass*, int32> FYetAnotherNodeClassHelper::BlueprintClassCount;
FYetAnotherNodeClassHelper::FOnPackageListUpdated FYetAnotherNodeClassHelper::OnPackageListUpdated;

FYetAnotherNodeClassHelper::FYetAnotherNodeClassHelper(UClass* InRootClass)
{
	RootNodeClass = InRootClass;
	// Register with the Asset Registry to be informed when it is done loading up files.
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::GetModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	AssetRegistryModule.Get().OnFilesLoaded().AddRaw(this, &FYetAnotherNodeClassHelper::InvalidateCache);
	AssetRegistryModule.Get().OnAssetAdded().AddRaw(this, &FYetAnotherNodeClassHelper::OnAssetAdded);
	AssetRegistryModule.Get().OnAssetRemoved().AddRaw(this, &FYetAnotherNodeClassHelper::OnAssetRemoved);

	// Register to have Populate called when doing a Hot Reload.
	IHotReloadInterface& HotReloadSupport = FModuleManager::LoadModuleChecked<IHotReloadInterface>("HotReload");
	HotReloadSupport.OnHotReload().AddRaw(this, &FYetAnotherNodeClassHelper::OnHotReload);

	// Register to have Populate called when a Blueprint is compiled.
	GEditor->OnBlueprintCompiled().AddRaw(this, &FYetAnotherNodeClassHelper::InvalidateCache);
	GEditor->OnClassPackageLoadedOrUnloaded().AddRaw(this, &FYetAnotherNodeClassHelper::InvalidateCache);

	UpdateAvailableBlueprintClasses();
}

FYetAnotherNodeClassHelper::~FYetAnotherNodeClassHelper()
{
	// Unregister with the Asset Registry to be informed when it is done loading up files.
	if (FModuleManager::Get().IsModuleLoaded(TEXT("AssetRegistry")))
	{
		FAssetRegistryModule& AssetRegistryModule = FModuleManager::GetModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
		AssetRegistryModule.Get().OnFilesLoaded().RemoveAll(this);
		AssetRegistryModule.Get().OnAssetAdded().RemoveAll(this);
		AssetRegistryModule.Get().OnAssetRemoved().RemoveAll(this);

		// Unregister to have Populate called when doing a Hot Reload.
		if (FModuleManager::Get().IsModuleLoaded(TEXT("HotReload")))
		{
			IHotReloadInterface& HotReloadSupport = FModuleManager::GetModuleChecked<IHotReloadInterface>("HotReload");
			HotReloadSupport.OnHotReload().RemoveAll(this);
		}

		// Unregister to have Populate called when a Blueprint is compiled.
		if (UObjectInitialized())
		{
			// GEditor can't have been destructed before we call this or we'll crash.
			GEditor->OnBlueprintCompiled().RemoveAll(this);
			GEditor->OnClassPackageLoadedOrUnloaded().RemoveAll(this);
		}
	}
}

void FYetAnotherNodeClassNode::AddUniqueSubNode(TSharedPtr<FYetAnotherNodeClassNode> SubNode)
{
	for (int32 Idx = 0; Idx < SubNodes.Num(); Idx++)
	{
		if (SubNode->Data.GetClassName() == SubNodes[Idx]->Data.GetClassName())
		{
			return;
		}
	}

	SubNodes.Add(SubNode);
}

void FYetAnotherNodeClassHelper::GatherClasses(const UClass* BaseClass, TArray<FYetAnotherNodeClassData>& AvailableClasses)
{
	const FString BaseClassName = BaseClass->GetName();
	if (!RootNode.IsValid())
	{
		BuildClassGraph();
	}

	TSharedPtr<FYetAnotherNodeClassNode> BaseNode = FindBaseClassNode(RootNode, BaseClassName);
	FindAllSubClasses(BaseNode, AvailableClasses);
}

FString FYetAnotherNodeClassHelper::GetDeprecationMessage(const UClass* Class)
{
	static FName MetaDeprecated = TEXT("DeprecatedNode");
	static FName MetaDeprecatedMessage = TEXT("DeprecationMessage");
	FString DefDeprecatedMessage("Please remove it!");
	FString DeprecatedPrefix("DEPRECATED");
	FString DeprecatedMessage;

	if (Class && Class->HasAnyClassFlags(CLASS_Native) && Class->HasMetaData(MetaDeprecated))
	{
		DeprecatedMessage = DeprecatedPrefix + TEXT(": ");
		DeprecatedMessage += Class->HasMetaData(MetaDeprecatedMessage) ? Class->GetMetaData(MetaDeprecatedMessage) : DefDeprecatedMessage;
	}

	return DeprecatedMessage;
}

bool FYetAnotherNodeClassHelper::IsClassKnown(const FYetAnotherNodeClassData& ClassData)
{
	return !ClassData.IsBlueprint() || !UnknownPackages.Contains(*ClassData.GetPackageName());
}

void FYetAnotherNodeClassHelper::AddUnknownClass(const FYetAnotherNodeClassData& ClassData)
{
	if (ClassData.IsBlueprint())
	{
		UnknownPackages.AddUnique(*ClassData.GetPackageName());
	}
}

bool FYetAnotherNodeClassHelper::IsHidingParentClass(UClass* Class)
{
	static FName MetaHideParent = TEXT("HideParentNode");
	return Class && Class->HasAnyClassFlags(CLASS_Native) && Class->HasMetaData(MetaHideParent);
}

bool FYetAnotherNodeClassHelper::IsHidingClass(UClass* Class)
{
	static FName MetaHideInEditor = TEXT("HiddenNode");
	return Class && Class->HasAnyClassFlags(CLASS_Native) && Class->HasMetaData(MetaHideInEditor);
}

bool FYetAnotherNodeClassHelper::IsPackageSaved(FName PackageName)
{
	const bool bFound = FPackageName::SearchForPackageOnDisk(PackageName.ToString());
	return bFound;
}

void FYetAnotherNodeClassHelper::OnAssetAdded(const struct FAssetData& AssetData)
{
	TSharedPtr<FYetAnotherNodeClassNode> Node = CreateClassDataNode(AssetData);

	TSharedPtr<FYetAnotherNodeClassNode> ParentNode;
	if (Node.IsValid())
	{
		ParentNode = FindBaseClassNode(RootNode, Node->ParentClassName);

		if (!IsPackageSaved(AssetData.PackageName))
		{
			UnknownPackages.AddUnique(AssetData.PackageName);
		}
		else
		{
			const int32 PrevListCount = UnknownPackages.Num();
			UnknownPackages.RemoveSingleSwap(AssetData.PackageName);

			if (UnknownPackages.Num() != PrevListCount)
			{
				OnPackageListUpdated.Broadcast();
			}
		}
	}

	if (ParentNode.IsValid())
	{
		ParentNode->AddUniqueSubNode(Node);
		Node->ParentNode = ParentNode;
	}

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	if (!AssetRegistryModule.Get().IsLoadingAssets())
	{
		UpdateAvailableBlueprintClasses();
	}
}

void FYetAnotherNodeClassHelper::OnAssetRemoved(const struct FAssetData& AssetData)
{
	FString AssetClassName;
	if (AssetData.GetTagValue(FBlueprintTags::GeneratedClassPath, AssetClassName))
	{
		ConstructorHelpers::StripObjectClass(AssetClassName);
		AssetClassName = FPackageName::ObjectPathToObjectName(*AssetClassName);

		TSharedPtr<FYetAnotherNodeClassNode> Node = FindBaseClassNode(RootNode, AssetClassName);
		if (Node.IsValid() && Node->ParentNode.IsValid())
		{
			Node->ParentNode->SubNodes.RemoveSingleSwap(Node);
		}
	}

	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	if (!AssetRegistryModule.Get().IsLoadingAssets())
	{
		UpdateAvailableBlueprintClasses();
	}
}

void FYetAnotherNodeClassHelper::InvalidateCache()
{
	RootNode.Reset();

	UpdateAvailableBlueprintClasses();
}

void FYetAnotherNodeClassHelper::OnHotReload(bool bWasTriggeredAutomatically)
{
	InvalidateCache();
}

TSharedPtr<FYetAnotherNodeClassNode> FYetAnotherNodeClassHelper::CreateClassDataNode(const struct FAssetData& AssetData)
{
	TSharedPtr<FYetAnotherNodeClassNode> Node;

	FString AssetClassName;
	FString AssetParentClassName;
	if (AssetData.GetTagValue(FBlueprintTags::GeneratedClassPath, AssetClassName) && AssetData.GetTagValue(FBlueprintTags::ParentClassPath, AssetParentClassName))
	{
		UObject* Outer1(NULL);
		ResolveName(Outer1, AssetClassName, false, false);

		UObject* Outer2(NULL);
		ResolveName(Outer2, AssetParentClassName, false, false);

		Node = MakeShareable(new FYetAnotherNodeClassNode);
		Node->ParentClassName = AssetParentClassName;

		UObject* AssetOb = AssetData.IsAssetLoaded() ? AssetData.GetAsset() : NULL;
		UBlueprint* AssetBP = Cast<UBlueprint>(AssetOb);
		UClass* AssetClass = AssetBP ? *AssetBP->GeneratedClass : AssetOb ? AssetOb->GetClass() : NULL;

		FYetAnotherNodeClassData NewData(AssetData.AssetName.ToString(), AssetData.PackageName.ToString(), AssetClassName, AssetClass);
		Node->Data = NewData;
	}

	return Node;
}

TSharedPtr<FYetAnotherNodeClassNode> FYetAnotherNodeClassHelper::FindBaseClassNode(TSharedPtr<FYetAnotherNodeClassNode> Node, const FString& ClassName)
{
	TSharedPtr<FYetAnotherNodeClassNode> RetNode;
	if (Node.IsValid())
	{
		if (Node->Data.GetClassName() == ClassName)
		{
			return Node;
		}

		for (int32 i = 0; i < Node->SubNodes.Num(); i++)
		{
			RetNode = FindBaseClassNode(Node->SubNodes[i], ClassName);
			if (RetNode.IsValid())
			{
				break;
			}
		}
	}

	return RetNode;
}

void FYetAnotherNodeClassHelper::FindAllSubClasses(TSharedPtr<FYetAnotherNodeClassNode> Node, TArray<FYetAnotherNodeClassData>& AvailableClasses)
{
	if (Node.IsValid())
	{
		if (!Node->Data.IsAbstract() && !Node->Data.IsDeprecated() && !Node->Data.bIsHidden)
		{
			AvailableClasses.Add(Node->Data);
		}

		for (int32 i = 0; i < Node->SubNodes.Num(); i++)
		{
			FindAllSubClasses(Node->SubNodes[i], AvailableClasses);
		}
	}
}

UClass* FYetAnotherNodeClassHelper::FindAssetClass(const FString& GeneratedClassPackage, const FString& AssetName)
{
	UPackage* Package = FindPackage(NULL, *GeneratedClassPackage);
	if (Package)
	{
		UObject* Object = FindObject<UObject>(Package, *AssetName);
		if (Object)
		{
			UBlueprint* BlueprintOb = Cast<UBlueprint>(Object);
			return BlueprintOb ? *BlueprintOb->GeneratedClass : Object->GetClass();
		}
	}

	return NULL;
}

void FYetAnotherNodeClassHelper::BuildClassGraph()
{
	TArray<TSharedPtr<FYetAnotherNodeClassNode> > NodeList;
	TArray<UClass*> HideParentList;
	RootNode.Reset();

	// gather all native classes
	for (TObjectIterator<UClass> It; It; ++It)
	{
		UClass* TestClass = *It;
		if (TestClass->HasAnyClassFlags(CLASS_Native) && TestClass->IsChildOf(RootNodeClass))
		{
			TSharedPtr<FYetAnotherNodeClassNode> NewNode = MakeShareable(new FYetAnotherNodeClassNode);
			NewNode->ParentClassName = TestClass->GetSuperClass()->GetName();

			FString DeprecatedMessage = GetDeprecationMessage(TestClass);
			FYetAnotherNodeClassData NewData(TestClass, DeprecatedMessage);

			NewData.bHideParent = IsHidingParentClass(TestClass);
			if (NewData.bHideParent)
			{
				HideParentList.Add(TestClass->GetSuperClass());
			}

			NewData.bIsHidden = IsHidingClass(TestClass);

			NewNode->Data = NewData;

			if (TestClass == RootNodeClass)
			{
				RootNode = NewNode;
			}

			NodeList.Add(NewNode);
		}
	}

	// find all hidden parent classes
	for (int32 i = 0; i < NodeList.Num(); i++)
	{
		TSharedPtr<FYetAnotherNodeClassNode> TestNode = NodeList[i];
		if (HideParentList.Contains(TestNode->Data.GetClass()))
		{
			TestNode->Data.bIsHidden = true;
		}
	}

	// gather all blueprints
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
	TArray<FAssetData> BlueprintList;

	FARFilter Filter;
	Filter.ClassNames.Add(UBlueprint::StaticClass()->GetFName());
	AssetRegistryModule.Get().GetAssets(Filter, BlueprintList);

	for (int32 i = 0; i < BlueprintList.Num(); i++)
	{
		TSharedPtr<FYetAnotherNodeClassNode> NewNode = CreateClassDataNode(BlueprintList[i]);
		NodeList.Add(NewNode);
	}

	// build class tree
	AddClassGraphChildren(RootNode, NodeList);
}

void FYetAnotherNodeClassHelper::AddClassGraphChildren(TSharedPtr<FYetAnotherNodeClassNode> Node, TArray<TSharedPtr<FYetAnotherNodeClassNode> >& NodeList)
{
	if (!Node.IsValid())
	{
		return;
	}

	const FString NodeClassName = Node->Data.GetClassName();
	for (int32 i = NodeList.Num() - 1; i >= 0; i--)
	{
		if (NodeList[i]->ParentClassName == NodeClassName)
		{
			TSharedPtr<FYetAnotherNodeClassNode> MatchingNode = NodeList[i];
			NodeList.RemoveAt(i);

			MatchingNode->ParentNode = Node;
			Node->SubNodes.Add(MatchingNode);

			AddClassGraphChildren(MatchingNode, NodeList);
		}
	}
}

int32 FYetAnotherNodeClassHelper::GetObservedBlueprintClassCount(UClass* BaseNativeClass)
{
	return BlueprintClassCount.FindRef(BaseNativeClass);
}

void FYetAnotherNodeClassHelper::AddObservedBlueprintClasses(UClass* BaseNativeClass)
{
	BlueprintClassCount.Add(BaseNativeClass, 0);
}

void FYetAnotherNodeClassHelper::UpdateAvailableBlueprintClasses()
{
	if (FModuleManager::Get().IsModuleLoaded(TEXT("AssetRegistry")))
	{
		FAssetRegistryModule& AssetRegistryModule = FModuleManager::GetModuleChecked<FAssetRegistryModule>(TEXT("AssetRegistry"));
		const bool bSearchSubClasses = true;

		TArray<FName> ClassNames;
		TSet<FName> DerivedClassNames;

		for (TMap<UClass*, int32>::TIterator It(BlueprintClassCount); It; ++It)
		{
			ClassNames.Reset();
			ClassNames.Add(It.Key()->GetFName());

			DerivedClassNames.Empty(DerivedClassNames.Num());
			AssetRegistryModule.Get().GetDerivedClassNames(ClassNames, TSet<FName>(), DerivedClassNames);

			int32& Count = It.Value();
			Count = DerivedClassNames.Num();
		}
	}
}

#undef LOCTEXT_NAMESPACE