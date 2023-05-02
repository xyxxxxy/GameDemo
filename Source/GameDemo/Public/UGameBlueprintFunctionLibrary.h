
#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "SItem.h"
#include "UGameBlueprintFunctionLibrary.generated.h"

struct FSItem;
struct FSItemCategory;
class ASGameCharacter;

UCLASS(meta=( DisplayName = "GameLibrary"))
class GAMEDEMO_API UGameBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable,Category="GameLibrary | Player")
	static ASGameCharacter* GetPlayer();
	
	UFUNCTION(BlueprintCallable,Category="GameLibrary | Player")
	static void EnabledInput(bool bIsEnabled);

	UFUNCTION(BlueprintCallable,Category="GameLibrary | Item")
	static void FindItemInDataTable( FSItem item,bool& bIsFound,FSItemCategory& Category);
};
