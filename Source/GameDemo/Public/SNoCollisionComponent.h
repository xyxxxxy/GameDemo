// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/SActionInterface.h"
#include "Components/ActorComponent.h"
#include "SNoCollisionComponent.generated.h"

class USoundCue;
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEffectStart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnEffectEnd);

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEDEMO_API USNoCollisionComponent : public UActorComponent, public ISActionInterface
{
	GENERATED_BODY()

public:
	
	UPROPERTY(BlueprintAssignable)
	FOnEffectStart OnEffectStart;
	
	UPROPERTY(BlueprintAssignable)
	FOnEffectEnd OnEffectEnd;
	
	bool IsTranslucent() const;

	virtual void ActionInteract_Implementation(AActor* InstigatorActor) override;
	
protected:
	
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Time")
	float EffectTime;

	UPROPERTY(EditDefaultsOnly,Category="NoCollision")
	UMaterialInstance* TranslucentMaterial;

	UPROPERTY(EditDefaultsOnly,Category="NoCollision")
	FName TranslucentCollisionName;

	UPROPERTY(BlueprintReadWrite,Category = "Handle")
	FTimerHandle EffectTimer;

	UPROPERTY(EditDefaultsOnly,Category = "Sound")
	USoundBase* RecoverSound;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Physics")
	bool bShouldSimulatePhysics = false;

	UPROPERTY()
	UStaticMeshComponent* CollisionComp;

	FTimerDelegate EffectDelegate;

	UFUNCTION()
	void Recover(AActor* InstigatorActor);

	void SetNoCollisionMaterial();

	bool UpdateMaterial(UMaterialInstance* NewMaterial);

	void ClearTimer();

	UFUNCTION(BlueprintImplementableEvent,Category = "Action |UI",meta = ( DisplayName = "CreateTimeWidget"))
	void K2_CreateTimeWidget();

	virtual void BeginPlay() override;


private:
	
	UPROPERTY()
	AActor* ParentActor;

	bool bIsTranslucent;
	
};
