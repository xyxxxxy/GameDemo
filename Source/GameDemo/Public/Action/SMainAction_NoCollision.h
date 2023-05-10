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
	UMaterialInstance* TranslucentMaterial;
	
	UPROPERTY(EditDefaultsOnly,Category="NoCollision")
	FName NewCollisionName;
	
	UPROPERTY(EditDefaultsOnly,Category="NoCollision")
	float EffectTime;

	FTimerHandle RecoverTimer;

	FTimerDelegate RecoverDelegate;

	UFUNCTION()
	void RecoverMaterial(AActor* Instigator);

	UFUNCTION(BlueprintCallable,BlueprintPure,Category="Action")
	bool IsValidTime() const;
	
	void ClearRecoverTimer();
	
	bool UpdateSingleMaterial(UPrimitiveComponent* PrimitiveComp,UMaterialInstance* NewMaterial);

	bool EliminateCollisionTrace(AActor* Instigator);

	void SetNoCollisionMaterial(UPrimitiveComponent* PrimitiveComp,AActor* Instigator);



	virtual void InitialVariable() override;
private:

	UPROPERTY()
	UPrimitiveComponent* HitComponent;

	bool bIsValidTime = true;
	
public:
	
	virtual void StartAction_Implementation(AActor* Instigator) override;
	
	virtual void TraceInspection_Implementation(AActor* Instigator) override;

	virtual bool ShouldStartMainAction(AActor* Instigator) override;

	virtual void UpdateMaterials(TArray<AStaticMeshActor*> Actors, bool bIsToDeploy) override;
};


