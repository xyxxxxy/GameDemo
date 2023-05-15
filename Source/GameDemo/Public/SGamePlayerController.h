// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SUIManagerInterface.h"
#include "GameFramework/PlayerController.h"
#include "SGamePlayerController.generated.h"

class UUserWidget;

UCLASS()
class GAMEDEMO_API ASGamePlayerController : public APlayerController,public ISUIManagerInterface
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly,Category="UI")
	TSubclassOf<UUserWidget> DefaultMainWidgetClass;

	UPROPERTY(EditDefaultsOnly,Category="UI")
	float DelayTime = 1.0f;

	FTimerHandle WidgetTimer;

	FTimerDelegate WidgetDelegate;
	
	virtual void OnPossess(APawn* InPawn) override;


public:

	UFUNCTION(BlueprintCallable,Category="UI")
	void CreateMainWidget();

	
	

private:

	UPROPERTY()
	UUserWidget* MainWidgetInstance;
};
