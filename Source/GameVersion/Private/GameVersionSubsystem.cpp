// Plugin developed by XZCendence.


#include "GameVersionSubsystem.h"
#include "Json.h"

DEFINE_LOG_CATEGORY(LogGameVersionSubsystem);


void UGameVersionSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	//Call the parent initialize function
	Super::Initialize(Collection);
	InitGameVersion();
	//GetLiveVersion();
}

void UGameVersionSubsystem::InitGameVersion()
{
	GameVersionSettings = GetMutableDefault<UGameVersionSettings>();

	//Populate the GameVersion attributes struct from the game version settings.
	GameVersion.BuildNumber = GameVersionSettings->BuildNumber;
	GameVersion.BuildName = GameVersionSettings->BuildName;
	GameVersion.ReleasePhase = GameVersionSettings->ReleasePhase;
	GameVersion.BuildSandbox = GameVersionSettings->BuildSandbox;
	GameVersion.SemanticVersionNumber = GameVersionSettings->SemanticVersionNumber;

	//Preprocessor directives for determining if this is a development build or not
	#if UE_BUILD_DEVELOPMENT
		GameVersion.bIsDevelopmentBuild = true;
	#endif

	#if UE_BUILD_SHIPPING
		GameVersion.bIsDevelopmentBuild = false;
	#endif
	
	GameVersion.SessionInterfaceGuid = GameVersionSettings->SessionInterfaceGUID;
}

void UGameVersionSubsystem::Deinitialize()
{
	//Nobody's home.
}

bool UGameVersionSubsystem::RequestLiveVersion()
{
	//Create the FHttpRequestRef
	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UGameVersionSubsystem::OnResponseReceived);
	Request->SetURL(GameVersionSettings->StaticVersionServiceEndpoint);
	Request->SetVerb("GET");
	Request->SetHeader(TEXT("User-Agent"), GameVersion.BuildName);
	Request->SetHeader("Content-Type", TEXT("application/json"));
	bool bSuccess = Request->ProcessRequest();
	if (bSuccess)
	{
		return true;
	}
	UE_LOG(LogGameVersionSubsystem, Error, TEXT("Failed to process live version request"));
	return false;
}

void UGameVersionSubsystem::OnResponseReceived(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if (bConnectedSuccessfully)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, FString::Printf(TEXT("Response was %s"), *(Response->GetContentAsString())));
		TSharedPtr<FJsonObject> ResponseObj;
		TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
		if (!FJsonSerializer::Deserialize(JsonReader, ResponseObj))
		{
			OnVersionRequestResponseReceived.Broadcast(LiveVersionAttr, SessionInterfaceTransientConfig, false);
			UE_LOG(LogGameVersionSubsystem, Error, TEXT("Failed to deserialize JSON from static version service endpoint response"));
		}
		else
		{
			ProcessResponse(ResponseObj);
		}

	}
	else
	{
		UE_LOG(LogGameVersionSubsystem, Error, TEXT("Could not make a successful connection to the static version service endpoint"));
	}
}


void UGameVersionSubsystem::ProcessResponse(const TSharedPtr<FJsonObject> ResponseObj)
{
	//True if we were able to parse all these fields from the JSON successfully.
	bool bSuccess;
	//TODO: We should probably use the "Try" variant of all these field getter functions to make this code safer. That would of course make it more convoluted, but alas.
	bSuccess = ResponseObj->TryGetNumberField("liveBuildNumber", LiveVersionAttr.BuildNumber);
	bSuccess = ResponseObj->TryGetStringField("liveBuildName", LiveVersionAttr.BuildName);
	bSuccess = ResponseObj->TryGetStringField("liveReleasePhase", LiveVersionAttr.ReleasePhase);
	bSuccess = ResponseObj->TryGetStringField("liveVersionNumber", LiveVersionAttr.SemanticVersionNumber);
	bSuccess = ResponseObj->TryGetStringField("liveBuildSandbox", LiveVersionAttr.BuildSandbox);
	FString LiveBuildConfig;
	bSuccess = 	ResponseObj->TryGetStringField("liveBuildConfiguration", LiveBuildConfig);
	LiveVersionAttr.bIsDevelopmentBuild = (LiveBuildConfig == "Development");
	bSuccess = FGuid::Parse(*ResponseObj->GetStringField("liveSessionIfaceGuid"), LiveVersionAttr.SessionInterfaceGuid);
	const TSharedPtr<FJsonObject>* VersionRestrictionConfigUtilityObject;
	//Now we populate the fields in the live SessionInterfaceTransientConfig
	if (ResponseObj->TryGetObjectField("versionRestrictionConfig", VersionRestrictionConfigUtilityObject))
	{
		bSuccess = VersionRestrictionConfigUtilityObject->Get()->TryGetBoolField("markAllOldAsDirty", SessionInterfaceTransientConfig.bMarkAllOldAsDirty);
		bSuccess = VersionRestrictionConfigUtilityObject->Get()->TryGetBoolField("restrictSessionIfaceToLive", SessionInterfaceTransientConfig.bRestrictSessionIfaceToLive);
		bSuccess = VersionRestrictionConfigUtilityObject->Get()->TryGetBoolField("restrictSessionIfaceToGUID", SessionInterfaceTransientConfig.bRestrictSessionIfaceToGUID);
		bSuccess = VersionRestrictionConfigUtilityObject->Get()->TryGetBoolField("enableSessionIfaceForLive", SessionInterfaceTransientConfig.bEnableSessionIface);
		OnVersionRequestResponseReceived.Broadcast(LiveVersionAttr, SessionInterfaceTransientConfig, bSuccess);
		
	}
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, LiveVersionAttr.BuildName);

}

