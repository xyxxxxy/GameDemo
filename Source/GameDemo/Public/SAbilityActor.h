
#pragma once

#include "CoreMinimal.h"
#include "SOverlapActor.h"
#include "SAbilityActor.generated.h"


struct FSActionProperty;
class USAction;
UCLASS()
class GAMEDEMO_API ASAbilityActor : public ASOverlapActor
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Action")
	TSubclassOf<USAction> NewAction;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category="Action")
	FName ActionName;

public:

	UFUNCTION(BlueprintImplementableEvent,meta=(DisplayName = "CreateActionWidget"))
	void K2_CreateActionWidget();
	
	virtual void Interact_Implementation(APawn* InstigatorActor) override;

	virtual void OnConstruction(const FTransform& Transform) override;
	
	
};
