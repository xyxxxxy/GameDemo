// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Action/SActionData.h"
#include "SGamePlayerState.generated.h"

class USAction;
class USActionComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnActionSWitchedForPS,
	USAction*, OldAction,
	USAction*, NewAction,
	FSActionProperty, NewActionProperty);

UCLASS()
class GAMEDEMO_API ASGamePlayerState : public APlayerState
{
	GENERATED_BODY()

protected:

	UPROPERTY()
	TArray<USAction*> NormalActions;
	
	UPROPERTY()
	TArray<USAction*> MainActions;

	UPROPERTY()
	USAction* CurrentMainAction;

	UPROPERTY()
	TMap<FName,FSActionProperty> ActionProperties;

	virtual void BeginPlay() override;

	virtual void CopyProperties(APlayerState* PlayerState) override;
	
public:

	UFUNCTION(BlueprintCallable,BlueprintPure,Category="Action")
	bool HaveCurrentMainAction() const;
	
	UFUNCTION(BlueprintCallable,BlueprintPure,Category="Action")
	USAction* GetCurrentMainAction() const;

	UFUNCTION(BlueprintCallable,BlueprintPure,Category="Action")
	TArray<USAction*> GetNormalActions() const;

	UFUNCTION(BlueprintCallable,BlueprintPure,Category="Action")
	TArray<USAction*> GetMainActions() const;

	UFUNCTION(BlueprintCallable,Category="Action")
	void SetActionProperty(USActionComponent* Comp,USAction* NewAction);

	UFUNCTION(BlueprintCallable,Category="Action")
	void SetActionProperties(const TMap<FName,FSActionProperty>& NewActionProperties);

	UFUNCTION(BlueprintCallable,Category="Action")
	FSActionProperty GetActionProperty(FName ActionName);

	UFUNCTION(BlueprintCallable,Category="Action")
	void SetMainActions(TArray<USAction*> NewActions);

	UFUNCTION(BlueprintCallable,Category="Action")
	void SetCurrentMainAction(USAction* OldAction,USAction* NewAction);


	UPROPERTY(BlueprintAssignable)
	FOnActionSWitchedForPS OnActionSWitchedForPS;
	
};
