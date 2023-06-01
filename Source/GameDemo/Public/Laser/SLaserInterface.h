// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SLaserInterface.generated.h"

UINTERFACE(MinimalAPI)
class USLaserInterface : public UInterface
{
	GENERATED_BODY()
};

class GAMEDEMO_API ISLaserInterface
{
	GENERATED_BODY()


public:

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Action | Laser")
	void LaserInteract(AActor* InstigatorActor,bool bNewState);
	virtual void LaserInteract_Implementation(AActor* InstigatorActor,bool bNewState);
	
};
