// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SActionData.h"
#include "SActionInterface.h"
#include "UObject/NoExportTypes.h"
#include "SAction.generated.h"

class USActionComponent;
class UWorld;

static TAutoConsoleVariable<int32> CShowActionTrace(TEXT("Action.ShowTrace"),0,
											 TEXT("Enable Show Trace."),ECVF_Cheat);

UCLASS(Blueprintable)
class GAMEDEMO_API USAction : public UObject,public ISActionInterface
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditAnywhere,Category="Tags")
	FGameplayTagContainer BlockedTags;

	UPROPERTY(EditAnywhere,Category="Tags")
	FGameplayTagContainer GrantTags;
	
	UPROPERTY(EditDefaultsOnly,Category="Action")
	UAnimMontage* ActionAnimMontage;
	
	UPROPERTY(EditDefaultsOnly,Category="Action")
	bool bIsEnableTick = false;

	UPROPERTY(EditDefaultsOnly,Category="Action")
	TEnumAsByte<EActionCategory::Type> ActionCategory = EActionCategory::NormalAction;
	
	bool bIsRunning;
	
	UFUNCTION(BlueprintCallable,Category="Action")
	USActionComponent* GetOwningComponent() const;
	
public:
	
	UPROPERTY(EditDefaultsOnly,Category="Action")
	FName ActionName;

	virtual  UWorld* GetWorld() const override;

	UFUNCTION(BlueprintCallable,Category="Action")
	bool IsRunning() const;

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Action")
	bool CanStart(AActor* Instigator);
	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Action")
	void StartAction(AActor* Instigator);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Action")
	void StopAction(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="Action",meta=(DisplayName="StartDeploy"))
	void K2_StartDeploy(USActionComponent* OwningComp,AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable,Category="Action",meta=(DisplayName="EndDeploy"))
	void K2_EndDeploy(USActionComponent* OwningComp,AActor* Instigator);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent,Category="Action")
	void ValReset();

	virtual void InitialVariable();

	bool CanEnableTick() const;

	TEnumAsByte<EActionCategory::Type> GetActionCategory() const;
	
};
