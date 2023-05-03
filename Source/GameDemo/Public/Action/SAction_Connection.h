// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/SAction.h"
#include "SAction_Connection.generated.h"


UCLASS()
class GAMEDEMO_API USAction_Connection : public USAction
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	bool bIsStartSet = false;

	UPROPERTY()
	UPrimitiveComponent*  HitComponent;

	UPROPERTY(EditAnywhere,Category="Action")
	UPhysicalMaterial* ConnectionMaterial;

	UPROPERTY(EditAnywhere,Category = "Action")
	float TraceDistance;

	UPROPERTY(BlueprintReadOnly)
	FVector FirstLocation;

	UPROPERTY(BlueprintReadOnly)
	FVector SecondLocation;

	UFUNCTION()
	void FirstTrace(AActor* Instigator);

	UFUNCTION()
	void SecondTrace(AActor* Instigator);

	UFUNCTION(BlueprintImplementableEvent,meta=(DisplayName="SpawnConnection"))
	void K2_SpawnConnections();
public:

	virtual bool CanStart_Implementation(AActor* Instigator) override;

	virtual void StartAction_Implementation(AActor* Instigator) override;

	virtual void ValReset() override;
};


