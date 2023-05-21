// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/SActionInterface.h"
#include "GameFramework/Actor.h"
#include "SNoCollisionActor.generated.h"

class USoundCue;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEffectEnd);

UCLASS()
class GAMEDEMO_API ASNoCollisionActor : public AActor,public ISActionInterface
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintAssignable)
	FOnEffectEnd OnEffectEnd;
	
	ASNoCollisionActor();

	virtual void ActionInteract_Implementation(AActor* InstigatorActor) override;

	bool IsTranslucent() const;
	
protected:
	
	UPROPERTY(EditDefaultsOnly,Category="Component")
	USceneComponent* SceneComp;
	
	UPROPERTY(EditDefaultsOnly,Category="Component")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Time")
	float EffectTime;

	UPROPERTY(EditDefaultsOnly,Category="NoCollision")
	UMaterialInstance* TranslucentMaterial;

	UPROPERTY(EditDefaultsOnly,Category="NoCollision")
	FName TranslucentCollisionName;

	UPROPERTY(BlueprintReadOnly,Category = "Handle")
	FTimerHandle EffectTimer;

	UPROPERTY(EditDefaultsOnly,Category = "Sound")
	USoundBase* RecoverSound;

	FTimerDelegate EffectDelegate;

	UFUNCTION()
	void Recover(AActor* InstigatorActor);

	void SetNoCollisionMaterial();

	bool UpdateMaterial(UMaterialInstance* NewMaterial);

	void ClearTimer();

	UFUNCTION(BlueprintImplementableEvent,Category = "Action |UI",meta=( DisplayName = "CreateTimeWidget"))
	void K2_CreateTimeWidget();

private:

	bool bIsTranslucent;

	
	
};
