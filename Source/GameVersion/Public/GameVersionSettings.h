// Plugin developed by XZCendence.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameVersionSettings.generated.h"


UCLASS(config = GameVersionSettings)
class GAMEVERSION_API UGameVersionSettings : public UObject
{
	GENERATED_BODY()

public:

	UGameVersionSettings(const FObjectInitializer& obj);

	UPROPERTY(Config, EditAnywhere, Category = "Game Version Settings")
	int32 BuildNumber;

	UPROPERTY(Config, EditAnywhere, Category = "Game Version Settings")
	FString  StaticVersionServiceEndpoint;

	UPROPERTY(Config, EditAnywhere, Category = "Game Version Settings")
	FString  BuildSandbox;

	UPROPERTY(Config, EditAnywhere, Category = "Game Version Settings")
	FString  ReleasePhase;

	UPROPERTY(Config, EditAnywhere, Category = "Game Version Settings")
	FString  BuildName;

	UPROPERTY(Config, EditAnywhere, Category = "Game Version Settings")
	FString  SemanticVersionNumber;

	UPROPERTY(Config, EditAnywhere, Category = "Game Version Settings")
	FGuid SessionInterfaceGUID;
};