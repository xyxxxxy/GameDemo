// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SMainAction.h"
#include "SMainAction_NoCollision.generated.h"


UCLASS()
class GAMEDEMO_API USMainAction_NoCollision : public USMainAction
{
	GENERATED_BODY()
	
protected:
	
	
	UPROPERTY(EditDefaultsOnly,Category="NoCollision")
	TEnumAsByte<ECollisionChannel> CollisionChannel;
	
	UFUNCTION(BlueprintCallable,BlueprintPure,Category="Action")
	bool IsValidTime() const;

	UFUNCTION()
	void TimerCallBack();
	
	bool UpdateSingleMaterial(AActor* SingleActor,UMaterialInstance* NewMaterial);

	bool EliminateCollisionTrace(AActor* Instigator);
	

	
private:

	UPROPERTY()
	AActor* HitActor;
	
	bool bIsValidTime = true;
	
public:
	
	virtual void StartAction_Implementation(AActor* Instigator) override;
	
	virtual void TraceInspection_Implementation(AActor* InstigatorActor) override;

	virtual bool ShouldStartMainAction(AActor* Instigator) override;

	UFUNCTION(BlueprintCallable,Category="Action | Material")
	void UpdateMaterialsByNoCollision(TArray<AActor*> Actors, bool bIsToDeploy);
};


