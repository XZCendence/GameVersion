// Plugin developed by XZCendence.

#include "GameVersionEditor.h"
#include "GameVersionEditorStyle.h"
#include "GameVersionEditorCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"

static const FName GameVersionTabName("GameVersion");

#define LOCTEXT_NAMESPACE "FGameVersionEditorModule"

//Function called to initialize the module
void FGameVersionEditorModule::StartupModule()
{
	FGameVersionEditorStyle::Initialize();
	FGameVersionEditorStyle::ReloadTextures();
	FGameVersionEditorCommands::Register();
	PluginCommands = MakeShareable(new FUICommandList);
	PluginCommands->MapAction(
		FGameVersionEditorCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FGameVersionEditorModule::PluginButtonClicked),
		FCanExecuteAction());
	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FGameVersionEditorModule::RegisterMenus));
}

//Function called before unloading the module
void FGameVersionEditorModule::ShutdownModule()
{
	UToolMenus::UnRegisterStartupCallback(this);
	UToolMenus::UnregisterOwner(this);
	FGameVersionEditorStyle::Shutdown();
	FGameVersionEditorCommands::Unregister();
}

//Function called when the plugin icon is clicked in the editor toolbar
void FGameVersionEditorModule::PluginButtonClicked()
{
	
	/*FText DialogText = FText::FromString(TEXT("This is a dialog box"));
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);*/
}

void FGameVersionEditorModule::RegisterMenus()
{
	FToolMenuOwnerScoped OwnerScoped(this);
	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FGameVersionEditorCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FGameVersionEditorCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGameVersionEditorModule, GameVersion)