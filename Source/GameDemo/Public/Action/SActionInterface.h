// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SActionInterface.generated.h"

UINTERFACE(MinimalAPI)
class USActionInterface : public UInterface
{
	GENERATED_BODY()
};


class GAMEDEMO_API ISActionInterface
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent,Category="Action")
	void TraceInspection(AActor* Instigator);
	virtual void TraceInspection_Implementation(AActor* Instigator);
};
