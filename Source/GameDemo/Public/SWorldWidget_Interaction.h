// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SWorldWidget.h"
#include "SWorldWidget_Interaction.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEMO_API USWorldWidget_Interaction : public USWorldWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Category")
	FName TextName;

protected:
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UFUNCTION(BlueprintCallable,Category="Interact")
	void SetTextName();
};
