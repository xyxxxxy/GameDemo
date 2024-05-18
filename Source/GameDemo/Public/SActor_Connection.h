// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SActor_Connection.generated.h"

UCLASS()
class GAMEDEMO_API ASActor_Connection : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASActor_Connection();

protected:
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Component")
	USceneComponent* RootComp;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Component")
	USceneComponent* SceneComp;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Component")
	UStaticMeshComponent* ConnectionComp;

	UPROPERTY()
	FVector RelativeLocation;

	UPROPERTY(BlueprintReadWrite)
	float Time;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite)
	float ExistTime = 30.0f;

	UFUNCTION()
	void Connect();

	virtual void BeginPlay() override;

	UFUNCTION()
	void StopGrow(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	
public:
	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Connection",meta=(ExposeOnSpawn))
	FVector StartLocation;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,Category="Connection",meta=(ExposeOnSpawn))
	FVector EndLocation;

	virtual void Tick(float DeltaTime) override;

};
