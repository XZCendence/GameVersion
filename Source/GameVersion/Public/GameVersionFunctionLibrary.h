// Plugin developed by XZCendence.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GameVersionFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class GAMEVERSION_API UGameVersionFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintPure, BlueprintCallable, Category = "Game Version Subsystem")
	static FString GetGameVersionString();
	
};
