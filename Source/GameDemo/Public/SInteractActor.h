// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SInteractInterface.h"
#include "SItem.h"
#include "GameFramework/Actor.h"
#include "SInteractActor.generated.h"

UCLASS()
class GAMEDEMO_API ASInteractActor : public AActor,public ISInteractInterface
{
	GENERATED_BODY()



public:	

	ASInteractActor();
	
	virtual void OnConstruction(const FTransform& Transform) override;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	FSItem Item;

	virtual void GetCategory_Implementation(FName& Name) override;

	UFUNCTION()
	virtual  void OnActorOverLap(UPrimitiveComponent* OverlappedComponent,AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult & SweepResult);
	

	
protected:
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Component")
	USceneComponent* SceneComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Component")
	UStaticMeshComponent* InteractComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Component")
	class USphereComponent* SphereComp;
	
	virtual void BeginPlay() override;

	void SetMesh();

	void ActorGetCategory(FName& CategoryName);
	
};
