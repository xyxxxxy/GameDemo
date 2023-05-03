// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SAction.h"
#include "Components/ActorComponent.h"
#include "SActionComponent.generated.h"


class USAction;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActionStateChanged,
	class USActionComponent*,OwningComp,
	USAction*, Action);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEDEMO_API USActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	USActionComponent();

protected:

	UPROPERTY(EditAnywhere,Category="Action")
	TArray<TSubclassOf<USAction>> DefaultActions;
	
	UPROPERTY(BlueprintReadOnly,Category="Action")
	TArray<USAction*> Actions;

	UPROPERTY(EditDefaultsOnly,Category="Action")
	USAction* MainActions;
	
	UPROPERTY(BlueprintReadOnly,Category="Action")
	FName MainActionsName;

	UPROPERTY()
	bool bIsMainActionDeployed = false;
	
	virtual void BeginPlay() override;

public:	

	UPROPERTY(BlueprintReadOnly,Category="Tag")
	FGameplayTagContainer ActiveTag;
	
	UFUNCTION(BlueprintCallable,Category="Action")
	void AddAction(AActor* Instigator,TSubclassOf<USAction> ActionClass);

	UFUNCTION(BlueprintCallable,Category="Action")
	bool StartActionByName(AActor* Instigator,FName Name);

	UFUNCTION(BlueprintCallable,Category="Action")
	bool StopActionByName(AActor* Instigator,FName Name);

	UFUNCTION(BlueprintCallable,Category="Action")
	void RemoveAction(AActor* Instigator,USAction* ActionToRemove);

	UFUNCTION(BlueprintCallable,Category="Action")
	void SwitchMainAction(AActor* Instigator,TSubclassOf<USAction> ActionSwitchTo);

	UFUNCTION(BlueprintCallable,Category="Action")
	bool IsMainActionDeployed() const;

	UFUNCTION()
	void SetMainActionDeployed(bool NewState);
	
	UPROPERTY(BlueprintAssignable)
	FOnActionStateChanged OnActionStarted;

	UPROPERTY(BlueprintAssignable)
	FOnActionStateChanged OnActionStopped;
};
