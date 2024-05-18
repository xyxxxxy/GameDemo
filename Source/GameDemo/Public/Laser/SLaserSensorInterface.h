// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SLaserSensorInterface.generated.h"


UINTERFACE(MinimalAPI)
class USLaserSensorInterface : public UInterface
{
	GENERATED_BODY()
};

class GAMEDEMO_API ISLaserSensorInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category = "Action | Laser")
	void SetState(AActor* InstigatorActor , bool NewState = false);
	virtual void SetState_Implementation(AActor* InstigatorActor , bool NewState = false);
};
