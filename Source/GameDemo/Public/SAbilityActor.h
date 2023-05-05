// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SOverlapActor.h"
#include "SAbilityActor.generated.h"


class USAction;
UCLASS()
class GAMEDEMO_API ASAbilityActor : public ASOverlapActor
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Action")
	TSubclassOf<USAction> NewAction;

public:
	virtual void Interact_Implementation(APawn* InstigatorActor) override;
	
};
