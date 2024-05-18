// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SUIManagerInterface.generated.h"


UINTERFACE(MinimalAPI)
class USUIManagerInterface : public UInterface
{
	GENERATED_BODY()
};

class GAMEDEMO_API ISUIManagerInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Action | UI")
	void PushWidget(const TSoftClassPtr<UUserWidget>& WidgetClass, bool bIsPlayAnimation = false);
	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Action | UI")
	void CloseUI();
	
	
};
