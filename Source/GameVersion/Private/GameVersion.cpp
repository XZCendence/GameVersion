// Plugin developed by XZCendence.

#include "GameVersion.h"
#include "CoreMinimal.h"
#include "ISettingsModule.h"
#include "GameVersionSettings.h"
#include "Modules/ModuleManager.h"

#define LOCTEXT_NAMESPACE "FGameVersionModule"

DEFINE_LOG_CATEGORY(LogGameVersion);

void FGameVersion::StartupModule()
{
	// This code will execute after your module is loaded into memory (but after global variables are initialized, of course.)
	//Initialize Settings Module
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "GameVersionSettings",
			LOCTEXT("RuntimeSettingsName", "Game Version"), LOCTEXT("RuntimeSettingsDescription", "Configure game version settings."),
			GetMutableDefault<UGameVersionSettings>());
	}
}


void FGameVersion::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

