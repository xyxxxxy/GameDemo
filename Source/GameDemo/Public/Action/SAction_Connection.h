// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/SAction.h"
#include "SAction_Connection.generated.h"


class ASActor_Connection;
class AStaticMeshActor;

UCLASS()
class GAMEDEMO_API USAction_Connection : public USAction
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Connection")
	UMaterialInstance* NormalMaterial;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Connection")
	UMaterialInstance* SelectedMaterial;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Connection")
	UMaterialInstance* DeployedMaterial;

	UPROPERTY(EditAnywhere,Category="Connection")
	UPhysicalMaterial* ConnectionMaterial;

	UPROPERTY(EditAnywhere,Category = "Connection")
	float TraceDistance;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Connection")
	FName ConnectionTag;

	UPROPERTY(BlueprintReadOnly,Category = "Connection")
	FVector FirstLocation;

	UPROPERTY(BlueprintReadOnly,Category = "Connection")
	FVector SecondLocation;

	UPROPERTY(EditAnywhere,Category="Connection")
	TSubclassOf<AActor> DefaultConnectionClass;

	UPROPERTY(EditAnywhere,Category="Sound")
	USoundBase* CollisionCue;
	
	UPROPERTY(EditAnywhere,Category="Obstacle")
	float TraceTolerance = 10.0f;

	UPROPERTY(EditAnywhere,Category="Obstacle")
	float SphereRadius;

	UFUNCTION(BlueprintCallable,Category="Connection")
	void UpdateMaterials(TArray<AStaticMeshActor*> Actors,bool bIsToDeploy);

	UFUNCTION(BlueprintImplementableEvent,meta=(DisplayName="SpawnConnection"))
	void K2_SpawnConnections();

	void FirstTrace(AActor* Instigator);

	void SecondTrace(AActor* Instigator);

	bool HasObstacle(AActor* Instigator);
	
	bool IsValidFace(int32 SectionIndex,UPrimitiveComponent* PrimitiveComp);

	bool UpdateSingleMaterial(int32 SectionIndex,UPrimitiveComponent* PrimitiveComp,UMaterialInstance* NewMaterial);

	virtual  void InitialVariable() override;

	bool IsConnectionClass(const FHitResult& HitResult) const;
	
private:

	UPROPERTY()
	bool bIsStartSet = false;

	UPROPERTY()
	UPrimitiveComponent*  HitComponent;
	
	UPROPERTY()
	AActor* FirstActor;
	
	UPROPERTY()
	UPrimitiveComponent*  TraceComponent;
	
	UPROPERTY()
	int32 PreSectionIndex = -1;

	UPROPERTY()	
	int32 FirstSectionIndex = -1;

	UPROPERTY()
	UPrimitiveComponent* FirstComponent;

	
public:
	
	virtual bool CanStart_Implementation(AActor* Instigator) override;

	virtual void StartAction_Implementation(AActor* Instigator) override;

	virtual void StopAction_Implementation(AActor* Instigator) override;
	
	virtual void TraceInspection_Implementation(AActor* Instigator) override;
	
};




