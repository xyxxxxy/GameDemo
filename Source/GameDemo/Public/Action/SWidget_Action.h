// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SAction.h"
#include "Blueprint/UserWidget.h"
#include "SWidget_Action.generated.h"

class USAction;

UCLASS(Blueprintable)
class GAMEDEMO_API USWidget_Action : public UUserWidget
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Action")
	FName ActionName;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Action")
	FSlateBrush IconBrush;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Action")
	FSActionProperty ActionProperty;

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="UI | Action")
	void SwitchAction(USAction* OldAction,USAction* NewAction,FSActionProperty Property);

public:

	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable,Category="UI | Action")
	void GetActionProperty();

};
