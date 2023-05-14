
#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"

DECLARE_LOG_CATEGORY_EXTERN(LogBarbelotUtilities, Log, All);

class FUnrealBarbelotUtilitiesModule : public IModuleInterface
{
public:

	static FUnrealBarbelotUtilitiesModule& Get()
	{
		return FModuleManager::Get().LoadModuleChecked<FUnrealBarbelotUtilitiesModule>(TEXT("UnrealBarbelotUtilities"));
	}

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
