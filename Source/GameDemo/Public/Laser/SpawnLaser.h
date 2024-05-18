// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnLaser.generated.h"

class UArrowComponent;

UCLASS()
class GAMEDEMO_API ASpawnLaser : public AActor
{
	GENERATED_BODY()
	
public:	

	ASpawnLaser();

protected:
	
	UPROPERTY(EditDefaultsOnly,Category="Component")
	UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Component")
	UArrowComponent* BeamArrow;

	UPROPERTY(EditAnywhere,Category = "Laser")
	TArray<AActor*> Sensors;

	UPROPERTY(EditDefaultsOnly)
	TEnumAsByte<ECollisionChannel> CollisionChannel;

	UPROPERTY(EditDefaultsOnly)
	UPhysicalMaterial* DesiredPhysicsMaterial;

	UPROPERTY(BlueprintReadWrite)
	TArray<AActor*> BeamActors;
	
	UFUNCTION(BlueprintCallable)
	void ClearBeams();

	UFUNCTION(BlueprintCallable)
	void CastLight(FVector Origin,FVector Direction,float Distance = 1000.0f);

public:

	UFUNCTION(BlueprintImplementableEvent,meta=( DisplayName = "SpawnBeam"))
	void K2_SpawnBeam(FVector Start,FVector End);

};
