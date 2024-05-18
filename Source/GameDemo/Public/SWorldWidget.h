// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SUIManagerInterface.h"
#include "Blueprint/UserWidget.h"
#include "SWorldWidget.generated.h"


class USizeBox;
UCLASS(Blueprintable)
class GAMEDEMO_API USWorldWidget : public UUserWidget,public ISUIManagerInterface
{
	GENERATED_BODY()

protected:

	UPROPERTY(meta=(BindWidget))
	USizeBox* ParentBox;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetUILocation();
	
public:
	
	UPROPERTY(BlueprintReadWrite,Category="UI",meta=(ExposeOnSpawn = true))
	AActor* AttachedActor;
	
	UPROPERTY(EditAnywhere,Category="UI")
	FVector WorldOffset;
};
