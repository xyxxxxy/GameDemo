// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/SMainAction.h"
#include "SMainAction_Laser.generated.h"


UCLASS()
class GAMEDEMO_API USMainAction_Laser : public USMainAction
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Laser")
	TEnumAsByte<ECollisionChannel> CollisionChannel;

	UPROPERTY(EditDefaultsOnly ,Category = "Laser")
	FName BoneName;
	
	UPROPERTY(EditDefaultsOnly,Category = "Laser")
	float FirstDistance = 2000.0f;
	
	UPROPERTY(EditDefaultsOnly,Category = "Laser")
	float LaserDistance = 1500.0f;
	
	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> BeamActors;

	UFUNCTION(BlueprintCallable)
	void CastLight(AActor* InstigatorActor,FVector HandOrigin,FVector Origin,FVector Direction,float Distance);

	void ClearBeams();

public:

	
	UFUNCTION(BlueprintImplementableEvent,meta=( DisplayName = "SpawnBeam"))
	void K2_SpawnBeam(FVector Start,FVector End);

	virtual void TraceInspection_Implementation(AActor* InstigatorActor) override;

	virtual void K2_StartDeploy_Implementation(USActionComponent* OwningComp, AActor* Instigator) override;

	virtual void InitialVariable() override;

	virtual void StopAction_Implementation(AActor* Instigator) override;
};


