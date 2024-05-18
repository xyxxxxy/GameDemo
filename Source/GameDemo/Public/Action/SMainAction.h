// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/SAction.h"
#include "SMainAction.generated.h"

/**
 * 
 */
UCLASS()
class GAMEDEMO_API USMainAction : public USAction
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Material")
	UMaterialInstance* NormalMaterial;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Material")
	UMaterialInstance* SelectedMaterial;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Material")
	UMaterialInstance* DeployedMaterial;
	
	UPROPERTY(EditAnywhere,Category="Material")
	UPhysicalMaterial* DesiredPhysicsMaterial;
	
	UPROPERTY(EditAnywhere,Category = "Action")
	float TraceDistance;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Action")
	FName AbilityTag;

	void SetProcessSettings(AActor* Instigator,bool bNewState);
	
public:
	
	virtual bool CanStart_Implementation(AActor* Instigator) override;

	virtual void StartAction_Implementation(AActor* Instigator) override;

	virtual void StopAction_Implementation(AActor* Instigator) override;

	virtual void K2_StartDeploy_Implementation(USActionComponent* OwningComp, AActor* Instigator) override;
	
	virtual bool ShouldStartMainAction(AActor* Instigator);

	UFUNCTION(BlueprintCallable,Category="Action | Material")
	virtual void UpdateMaterials(TArray<AStaticMeshActor*> Actors,bool bIsToDeploy);
};
