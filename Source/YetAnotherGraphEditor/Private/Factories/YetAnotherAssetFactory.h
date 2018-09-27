#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "YetAnotherAssetFactory.generated.h"

/**
 * 
 */
UCLASS()
class UYetAnotherAssetFactory : public UFactory
{
	GENERATED_BODY()
	
public:
	UYetAnotherAssetFactory();
	/**
	* Create a new object by class.
	*
	* @param InClass
	* @param InParent
	* @param InName
	* @param Flags
	* @param Context
	* @param Warn
	* @return The new object.
	*/
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn);

	
	
};
