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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnCreditsChanged,
	class ASGamePlayerState*,PlayerState,int32,NewCredits,int32,Delta);

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

	UFUNCTION(BlueprintCallable,BlueprintPure,Category="Action")
	const TMap<FName,FSActionProperty>& GetActionProperties();

	UFUNCTION(BlueprintCallable,BlueprintPure,Category="Action")
	FSActionProperty GetActionProperty(FName ActionName);

	UFUNCTION(BlueprintCallable,Category="Action")
	void SetMainActions(TArray<USAction*> NewActions);

	UFUNCTION(BlueprintCallable,Category="Action")
	void SetCurrentMainAction(USAction* OldAction,USAction* NewAction);

	UFUNCTION(BlueprintCallable,Category = "Score")
	void AddCredits(int32 Delta);

	UFUNCTION(BlueprintCallable,BlueprintPure,Category = "Score")
	int32 GetCredits() const;

	// UFUNCTION(BlueprintCallable,Category = "Score")
	// void RemoveCredits(int32 Delta);


	UPROPERTY(BlueprintAssignable,Category = "Events")
	FOnActionSWitchedForPS OnActionSWitchedForPS;

	UPROPERTY(BlueprintAssignable,Category = "Events")
	FOnCreditsChanged OnCreditsChanged;

private:

	int32 Credits = 0;
	
};
