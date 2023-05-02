// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/NoExportTypes.h"
#include "SAction.generated.h"

class USActionComponent;
class UWorld;

UCLASS(Blueprintable)
class GAMEDEMO_API USAction : public UObject
{
	GENERATED_BODY()

protected:
	
	UFUNCTION(BlueprintCallable,Category="Action")
	USActionComponent* GetOwningComponent() const;
	
	UPROPERTY(EditAnywhere,Category="Tags")
	FGameplayTagContainer BlockedTags;

	UPROPERTY(EditAnywhere,Category="Tags")
	FGameplayTagContainer GrantTags;

	bool bIsRunning;
	
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


};
