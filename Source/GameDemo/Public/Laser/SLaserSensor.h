// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SLaserSensorInterface.h"
#include "GameFramework/Actor.h"
#include "SLaserSensor.generated.h"

UCLASS()
class GAMEDEMO_API ASLaserSensor : public AActor,public ISLaserSensorInterface
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Laser")
	TArray<AActor*> InteractActors;

public:

	virtual void SetState_Implementation(AActor* InstigatorActor, bool NewState = false) override;

	

};
