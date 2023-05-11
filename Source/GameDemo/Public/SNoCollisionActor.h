// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/SActionInterface.h"
#include "GameFramework/Actor.h"
#include "SNoCollisionActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEffectEnd);

UCLASS()
class GAMEDEMO_API ASNoCollisionActor : public AActor,public ISActionInterface
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(EditDefaultsOnly,Category="Component")
	USceneComponent* SceneComp;
	
	UPROPERTY(EditDefaultsOnly,Category="Component")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditDefaultsOnly,Category="Time")
	float EffectTime;

	UPROPERTY(EditDefaultsOnly,Category="NoCollision")
	UMaterialInstance* TranslucentMaterial;

	UPROPERTY(EditDefaultsOnly,Category="NoCollision")
	FName NewCollisionName;

	FTimerHandle EffectTimer;

	FTimerDelegate EffectDelegate;

	UFUNCTION()
	void RecoverMaterial(AActor* InstigatorActor);

	void SetNoCollisionMaterial();

	bool UpdateMaterial(UMaterialInstance* NewMaterial);

	void ClearTimer();

public:
	UPROPERTY(BlueprintAssignable)
	FOnEffectEnd OnEffectEnd;
	
	ASNoCollisionActor();

	virtual void ActionInteract_Implementation(AActor* InstigatorActor) override;
	
};
