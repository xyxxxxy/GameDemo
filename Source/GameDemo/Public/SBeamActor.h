// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SBeamActor.generated.h"

UCLASS()
class GAMEDEMO_API ASBeamActor : public AActor
{
	GENERATED_BODY()
	
public:	

	ASBeamActor();

protected:

	UPROPERTY(EditDefaultsOnly,Category="Component")
	USceneComponent* SceneComp;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Component")
	UStaticMeshComponent* StaticMeshComp;

public:
	UFUNCTION(BlueprintCallable)
	void SetEnds(FVector Start, FVector End);

};
