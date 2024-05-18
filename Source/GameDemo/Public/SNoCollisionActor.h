// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SNoCollisionActor.generated.h"

class USNoCollisionComponent;
class USoundCue;

UCLASS()
class GAMEDEMO_API ASNoCollisionActor : public AActor
{
	GENERATED_BODY()
	
public:
	
	ASNoCollisionActor();

protected:
	
	UPROPERTY(EditDefaultsOnly,Category="Component")
	USceneComponent* SceneComp;
	
	UPROPERTY(EditDefaultsOnly,Category="Component")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category = "Component")
	USNoCollisionComponent* CollisionComp;
	
};
