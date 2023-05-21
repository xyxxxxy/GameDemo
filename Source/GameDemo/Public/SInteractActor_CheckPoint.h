// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SInteractActor.h"
#include "SInteractActor_CheckPoint.generated.h"

UCLASS()
class GAMEDEMO_API ASInteractActor_CheckPoint : public ASInteractActor
{
	GENERATED_BODY()

public:
	
	ASInteractActor_CheckPoint();

	virtual void Interact_Implementation(APawn* InstigatorActor) override;

protected:

	UPROPERTY(EditDefaultsOnly,Category = "Component")
	USceneComponent* PlayerLocationComp;

	UPROPERTY(EditDefaultsOnly,Category = "UI")
	TSubclassOf<UUserWidget> CheckWidgetClass;

	void Respawn(APawn* Pawn,APlayerController* PC);

	virtual void OnConstruction(const FTransform& Transform) override;
	
private:
	
	static int32 CPNumber;
	
	static ASInteractActor_CheckPoint* LastCheckPoint;

	UPROPERTY()
	UUserWidget* CheckWidgetInstance;
	
};
