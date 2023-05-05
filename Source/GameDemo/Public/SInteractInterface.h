
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SInteractInterface.generated.h"

UINTERFACE(MinimalAPI)
class USInteractInterface : public UInterface
{
	GENERATED_BODY()
};

class GAMEDEMO_API ISInteractInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="Interact")
	void Interact(APawn* InstigatorActor);
	virtual void Interact_Implementation(APawn* InstigatorActor);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="Interact")
	void GetCategory(FName& Name);
	virtual void GetCategory_Implementation(FName& Name);
};
