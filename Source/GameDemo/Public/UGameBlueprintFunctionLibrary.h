
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SItem.h"
#include "Action/SActionData.h"
#include "UGameBlueprintFunctionLibrary.generated.h"

class ASGameCharacter;

UCLASS(meta=( DisplayName = "GameLibrary"))
class GAMEDEMO_API UGameBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable,Category="GameLibrary | Player")
	static ASGameCharacter* GetPlayer();
	
	UFUNCTION(BlueprintCallable,Category="GameLibrary | Player")
	static void ControlPlayerInput(bool bIsEnabled);

	UFUNCTION(BlueprintCallable,Category="GameLibrary | Item")
	static void FindItemInDataTable( FSItem item,bool& bIsFound,FSItemCategory& Property);

	UFUNCTION(BlueprintCallable,Category="GameLibrary | Action")
	static void FindActionInDataTable( FName Name,bool& bIsFound,FSActionProperty& Property);
};
