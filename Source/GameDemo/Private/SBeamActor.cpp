// Fill out your copyright notice in the Description page of Project Settings.


#include "SBeamActor.h"



ASBeamActor::ASBeamActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneComp;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComp->SetupAttachment(SceneComp);

}

void ASBeamActor::SetEnds(FVector Start, FVector End)
{
	FVector Distance = End - Start;
	
	FVector Direction = Distance.GetSafeNormal();
	FRotator Rotation = FRotationMatrix::MakeFromZ(Direction).Rotator();
	StaticMeshComp->SetWorldLocationAndRotation(Start,Rotation,false,nullptr,ETeleportType::None);

	StaticMeshComp->SetWorldScale3D(FVector(0.05f,0.05f,Distance.Size()/100.0f));
}




