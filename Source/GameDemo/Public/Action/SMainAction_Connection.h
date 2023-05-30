// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/SMainAction.h"
#include "SMainAction_Connection.generated.h"


class ASActor_Connection;
class AStaticMeshActor;

UCLASS()
class GAMEDEMO_API USMainAction_Connection : public USMainAction
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(BlueprintReadOnly,Category = "Connection")
	FVector FirstLocation;

	UPROPERTY(BlueprintReadOnly,Category = "Connection")
	FVector SecondLocation;

	UPROPERTY(EditAnywhere,Category="Connection")
	TSubclassOf<AActor> DefaultConnectionClass;

	UPROPERTY(EditAnywhere,Category="Connection")
	TEnumAsByte<ECollisionChannel> NoCollisionChannel;

	UPROPERTY(EditAnywhere,Category="Connection")
	float TraceMagnification = 1.0f;

	UPROPERTY(EditAnywhere,Category="Sound")
	USoundBase* CollisionCue;
	
	UPROPERTY(EditAnywhere,Category="Obstacle")
	float TraceTolerance = 10.0f;

	UPROPERTY(EditAnywhere,Category="Obstacle")
	float SphereRadius;
	


	UFUNCTION(BlueprintImplementableEvent,meta=(DisplayName="SpawnConnection"))
	void K2_SpawnConnections();

	void FirstTrace(AActor* Instigator);

	void SecondTrace(AActor* Instigator);

	bool HasObstacle(AActor* Instigator);
	
	bool IsValidFace(int32 SectionIndex,UPrimitiveComponent* PrimitiveComp);

	bool UpdateSingleMaterial(int32 SectionIndex,UPrimitiveComponent* PrimitiveComp,UMaterialInstance* NewMaterial);

	virtual  void InitialVariable() override;

	bool IsConnectionClass(const FHitResult& HitResult) const;

	void ProbeNoCollision(AActor* InstigatorActor);
	
private:

	bool bIsFirstTraceSet = false;

	int32 PreSectionIndex = -1;

	int32 FirstSectionIndex = -1;

	float CurrentTraceDistance;
	
	UPROPERTY()
	UPrimitiveComponent*  HitComponent;
	
	UPROPERTY()
	AActor* FirstActor;
	
	UPROPERTY()
	UPrimitiveComponent*  TraceComponent;
	
	UPROPERTY()
	UPrimitiveComponent* FirstComponent;

public:
	
	virtual void StartAction_Implementation(AActor* Instigator) override;
	
	virtual void TraceInspection_Implementation(AActor* Instigator) override;

	virtual  void UpdateMaterials(TArray<AStaticMeshActor*> Actors,bool bIsToDeploy) override;
};




