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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActionDeployChanged,
	class USActionComponent*,OwningComp,
	AActor*, Instigator);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActionSwitched,
	USAction*, OldAction,
	USAction* ,NewAction);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnMainActionAcquired,
	class USActionComponent*,OwningComp,
	USAction*, Action);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEDEMO_API USActionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	USActionComponent();
	
private:

	bool bIsMainActionDeployed = false;

protected:

	UPROPERTY(EditAnywhere,Category="Action")
	TArray<TSubclassOf<USAction>> DefaultActions;

	UPROPERTY(EditAnywhere,Category="Action")
	TArray<TSubclassOf<USAction>> DefaultMainActions;
	
	UPROPERTY(BlueprintReadOnly,Category="Action")
	TArray<USAction*> Actions;
	
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadOnly,Category="Action")
	FName MainActionsName;

	UPROPERTY()
	USAction* CurrentMainAction;

	UPROPERTY()
	TArray<USAction*> MainActions;
	
	virtual void BeginPlay() override;

	void ActionTraceCheck();

public:	

	UPROPERTY(BlueprintReadWrite,Category="Tag")
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
	
	UFUNCTION(BlueprintCallable,Category="Action")
	bool ShouldStartDeploy(AActor* Instigator);

	UFUNCTION(BlueprintCallable,Category="Action")
	TArray<USAction*> GetMainActions() const;
	
	UFUNCTION()
	void SetMainActionDeployed(bool NewState);

	USAction* GetMainAction() const;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	bool HaveMainAction() const;

	void BindMainActionDeploy();

	void UnbindMainActionDeploy();

	void StopAllActions();
	
	UPROPERTY(BlueprintAssignable)
	FOnActionStateChanged OnActionStarted;

	UPROPERTY(BlueprintAssignable)
	FOnActionStateChanged OnActionStopped;

	UPROPERTY(BlueprintAssignable)
	FOnActionDeployChanged OnMainActionStartDeployed;

	UPROPERTY(BlueprintAssignable)
	FOnActionDeployChanged OnMainActionEndDeployed;

	UPROPERTY(BlueprintAssignable)
	FOnActionSwitched OnActionSwitched;

	UPROPERTY(BlueprintAssignable)
	FOnMainActionAcquired OnMainActionAcquired;
};


