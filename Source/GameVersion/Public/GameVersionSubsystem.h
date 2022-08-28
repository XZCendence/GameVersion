// Plugin developed by XZCendence.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Http.h"
#include "GameVersionSettings.h"
#include "Delegates/Delegate.h"
#include "GameVersionSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogGameVersionSubsystem, Log, All);

USTRUCT(BlueprintType)
struct FGameVersionAttributes
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Game Version Attributes")
	int32 BuildNumber;

	UPROPERTY(BlueprintReadWrite, Category = "Game Version Attributes")
	FString BuildName;

	UPROPERTY(BlueprintReadWrite, Category = "Game Version Attributes")
	FString SemanticVersionNumber;

	UPROPERTY(BlueprintReadWrite, Category = "Game Version Attributes")
	FString ReleasePhase;

	UPROPERTY(BlueprintReadWrite, Category = "Game Version Attributes")
	FString BuildSandbox;

	UPROPERTY(BlueprintReadWrite, Category = "Game Version Attributes")
	bool bIsDevelopmentBuild;

	UPROPERTY(BlueprintReadWrite, Category = "Game Version Attributes")
	FGuid SessionInterfaceGuid;
	
};

USTRUCT(BlueprintType)
struct FSessionInterfaceTransientConfig

{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, Category = "Game Version Attributes")
	bool bMarkAllOldAsDirty;

	UPROPERTY(BlueprintReadWrite, Category = "Game Version Attributes")
	bool bEnableSessionIface;

	UPROPERTY(BlueprintReadWrite, Category = "Game Version Attributes")
	bool bRestrictSessionIfaceToLive;

	UPROPERTY(BlueprintReadWrite, Category = "Game Version Attributes")
	bool bRestrictSessionIfaceToGUID;

};


/**
This class is a UGameInstanceSubsystem so that it gets created and destroyed along with the game instance, so we don't have to worry about GC destroying it.
This is similar to a singleton class, except that we don't need to worry about adding it to the root set, and it won't persist between PIE sessions.

 */
UCLASS()
class GAMEVERSION_API UGameVersionSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	/** This delegate was implemented mainly for blueprint binding purposes, we should probably get rid of this and use either a K2Node or a BlueprintAsyncActionBase to make things cleaner on the BP side.
	Using either of those two alternatives would also make error handling easier in general.
	*/
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FVersionRequestResponseDelegate, FGameVersionAttributes, LiveGameVersionAttributes, FSessionInterfaceTransientConfig, SessionIfaceTransientConfig, bool, bIsResponseValid);

	UFUNCTION(BlueprintCallable, Category = "Game Version Subsystem")
	bool RequestLiveVersion();

	UPROPERTY(BlueprintReadOnly, Category = "Game Version Subsystem")
	FGameVersionAttributes GameVersion;

	UPROPERTY(BlueprintReadOnly, Category = "Game Version Subsystem")
	FSessionInterfaceTransientConfig SessionInterfaceTransientConfig;

	UPROPERTY(BlueprintReadOnly, Category = "Game Version Subsystem")
	FGameVersionAttributes LiveVersionAttr;

	UPROPERTY(BlueprintAssignable, Category = "Game Version Subsystem")
	FVersionRequestResponseDelegate OnVersionRequestResponseReceived;

protected:

	UGameVersionSettings* GameVersionSettings;

	void OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully);

private:

	void InitGameVersion();

	void ProcessResponse(const TSharedPtr<FJsonObject> ResponseObj);

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;

	virtual void Deinitialize() override;

};