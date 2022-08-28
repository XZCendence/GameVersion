// Plugin developed by XZCendence.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "GameVersionEditorStyle.h"

class FGameVersionEditorCommands : public TCommands<FGameVersionEditorCommands>
{
public:

	FGameVersionEditorCommands()
		: TCommands<FGameVersionEditorCommands>(TEXT("GameVersion"), NSLOCTEXT("Contexts", "GameVersion", "GameVersion Plugin"), NAME_None, FGameVersionEditorStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
