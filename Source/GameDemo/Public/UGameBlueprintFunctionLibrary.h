
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SItem.h"
#include "Action/SActionData.h"
#include "UGameBlueprintFunctionLibrary.generated.h"

class ASGameCharacter;

UCLASS(meta=( DisplayName = "SGameLibrary"))
class GAMEDEMO_API UGameBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable,Category="GameLibrary | Player",meta=(WorldContext = "WorldContextObject"))
	static ASGameCharacter* GetPlayer(const UObject* WorldContextObject);
	
	UFUNCTION(BlueprintCallable,Category="GameLibrary | Player",meta=(WorldContext = "WorldContextObject"))
	static void ControlPlayerInput(const UObject* WorldContextObject,bool bIsEnabled);

	UFUNCTION(BlueprintCallable,Category="GameLibrary | Player",meta=(WorldContext = "WorldContextObject"))
	static void Rebirth(APawn* Pawn,APlayerController* PC,AActor* InstigatorActor);

	UFUNCTION(BlueprintCallable,Category="GameLibrary | Item")
	static void FindItemInDataTable( FSItem item,bool& bIsFound,FSItemProperty& Property);

	UFUNCTION(BlueprintCallable,Category="GameLibrary | Action")
	static void FindActionInDataTable( FName Name,bool& bIsFound,FSActionProperty& Property);
};
