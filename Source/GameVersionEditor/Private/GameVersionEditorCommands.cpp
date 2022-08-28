// Plugin developed by XZCendence.

#include "GameVersionEditorCommands.h"
#include "GameVersionSettings.h"

#define LOCTEXT_NAMESPACE "FGameVersionEditorModule"

void FGameVersionEditorCommands::RegisterCommands()
{
	UGameVersionSettings* GameVersionSettings = GetMutableDefault<UGameVersionSettings>();
	FString VersionNumber = GameVersionSettings->SemanticVersionNumber;

	UI_COMMAND(PluginAction, "Version: X", "Execute GameVersion action", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
