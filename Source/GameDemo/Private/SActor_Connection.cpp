// Fill out your copyright notice in the Description page of Project Settings.


#include "SActor_Connection.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASActor_Connection::ASActor_Connection()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComp=CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent=RootComp;

	SceneComp=CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	SceneComp->SetupAttachment(RootComp);
	
	ConnectionComp=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ConnectionComp"));
	ConnectionComp->SetupAttachment(SceneComp);

	RelativeLocation=ConnectionComp->GetRelativeLocation()*2.0f;
	Time=0.0f;
}


void ASActor_Connection::Connect()
{
	
	float TotalLength=UKismetMathLibrary::VSize(EndLocation-StartLocation);
	float EndScale=TotalLength/UKismetMathLibrary::VSize(RelativeLocation);
	float Scale = FMath::Lerp(1.0f,EndScale,Time);
	SetActorScale3D(FVector(Scale,1.0f,1.0f));
}

// Called every frame
void ASActor_Connection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(Time>=1.0f)
	{
		return;
	}
	Time+=DeltaTime;

}

