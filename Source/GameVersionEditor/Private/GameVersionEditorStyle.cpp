// Plugin developed by XZCendence.

#include "GameVersionEditorStyle.h"
#include "GameVersionEditor.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"

TSharedPtr< FSlateStyleSet > FGameVersionEditorStyle::StyleInstance = NULL;

void FGameVersionEditorStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FGameVersionEditorStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FGameVersionEditorStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("GameVersionEditorStyle"));
	return StyleSetName;
}

#define IMAGE_BRUSH( RelativePath, ... ) FSlateImageBrush( Style->RootToContentDir( RelativePath, TEXT(".png") ), __VA_ARGS__ )

const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);
const FVector2D Icon40x40(40.0f, 40.0f);

TSharedRef< FSlateStyleSet > FGameVersionEditorStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("GameVersionEditorStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("GameVersion")->GetBaseDir() / TEXT("Resources"));
	Style->Set("GameVersion.PluginAction", new IMAGE_BRUSH(TEXT("icon_Edit_Copy_40x"), Icon40x40));
	return Style;
}

#undef IMAGE_BRUSH

void FGameVersionEditorStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FGameVersionEditorStyle::Get()
{
	return *StyleInstance;
}
