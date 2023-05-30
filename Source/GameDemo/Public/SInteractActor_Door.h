// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SInteractActor.h"
#include "Components/TimelineComponent.h"
#include "SInteractActor_Door.generated.h"


UCLASS()
class GAMEDEMO_API ASInteractActor_Door : public ASInteractActor
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Component")
	UStaticMeshComponent* DoorFrameComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Component")
	UTimelineComponent* DoorTimelineComp;

	virtual void BeginPlay() override;

public:

	UPROPERTY(EditAnywhere,Category="Curve")
	UCurveFloat* DoorTimelineFloatCurve;
	
	ASInteractActor_Door();

	virtual void Interact_Implementation(APawn* InstigatorActor) override;

	

private:

	FOnTimelineFloat UpdateFunctionFloat;

	bool bIsOpen = false;
	
	UFUNCTION()
	void UpdateTimelineComp(float Output);
};
