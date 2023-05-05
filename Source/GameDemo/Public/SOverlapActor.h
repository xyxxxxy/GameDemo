// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SInteractInterface.h"
#include "GameFramework/Actor.h"
#include "SOverlapActor.generated.h"

class USphereComponent;
class UNiagaraComponent;
UCLASS()
class GAMEDEMO_API ASOverlapActor : public AActor,public ISInteractInterface
{
	GENERATED_BODY()
	
public:	
	
	ASOverlapActor();

protected:

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Component")
	USceneComponent* SceneComp;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Component")
	USphereComponent* SphereComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Component")
	UNiagaraComponent* NiagaraComp;

	virtual void BeginPlay() override;

public:	
	
	UFUNCTION()
	virtual  void OnActorOverLap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult & SweepResult);

	virtual void Interact_Implementation(APawn* InstigatorActor) override;
};
