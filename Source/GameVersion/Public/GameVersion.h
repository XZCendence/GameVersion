// Plugin developed by XZCendence.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"
#include "GameVersionSubsystem.h"
#include "Modules/ModuleManager.h"


DECLARE_LOG_CATEGORY_EXTERN(LogGameVersion, Log, All);


class GAMEVERSION_API IGameVersionModule : public IModuleInterface
{

public:

	static inline IGameVersionModule& Get()
	{
		return FModuleManager::LoadModuleChecked<IGameVersionModule>("GameVersion");
	}

	static inline bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("GameVersion");
	}
};

class GAMEVERSION_API FGameVersion : public IGameVersionModule
{
	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

public:

	UGameVersionSubsystem* GameVersionUtilityObject;

};

IMPLEMENT_MODULE(FGameVersion, GameVersion)

