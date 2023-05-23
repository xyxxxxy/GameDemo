// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SLaserInterface.h"
#include "GameFramework/Actor.h"
#include "LaserSensor.generated.h"

class UArrowComponent;

UCLASS()
class GAMEDEMO_API ALaserSensor : public AActor,public ISLaserInterface
{
	GENERATED_BODY()
	
public:	

	ALaserSensor();

protected:

	UPROPERTY(EditDefaultsOnly,Category="Component")
	USceneComponent* SceneComp;

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

	void ClearBeams();

	UFUNCTION(BlueprintCallable)
	void CastLight(FVector Origin,FVector Direction,float Distance = 1000.0f);

public:

	UFUNCTION(BlueprintImplementableEvent,meta=( DisplayName = "SpawnBeam"))
	void K2_SpawnBeam(FVector Start,FVector End);

};
