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
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="Action")
	void TraceInspection(AActor* InstigatorActor);
	virtual void TraceInspection_Implementation(AActor* InstigatorActor);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="Action")
	void ActionInteract(AActor* InstigatorActor);
	virtual void ActionInteract_Implementation(AActor* InstigatorActor);
	
};
