// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserSensor.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"


ALaserSensor::ALaserSensor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComp = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent = SceneComp;

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComp->SetupAttachment(SceneComp);

	BeamArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("BeamArrow"));
	BeamArrow->SetupAttachment(StaticMeshComp);
}


void ALaserSensor::ClearBeams()
{
	for(AActor* Actor : BeamActors)
	{
		Actor->Destroy();
	}
	BeamActors.Empty();
}

void ALaserSensor::CastLight(FVector Origin, FVector Direction, float Distance)
{
	FVector L_Origin = Origin;
	FVector L_Direction = Direction;
	float L_Distance = Distance;
	
	FVector BeamStart,BeamEnd;

	ClearBeams();
	
	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = true;
	QueryParams.bReturnPhysicalMaterial = true;
	QueryParams.AddIgnoredActor(this);
	
	bool bShouldContinue = true;
	
	while(bShouldContinue)
	{
		FHitResult LaserHitResult;
		
		FVector End = L_Origin + L_Direction * L_Distance;
		
		GetWorld()->LineTraceSingleByChannel(LaserHitResult,L_Origin,
			End,CollisionChannel,QueryParams);
		
		// Start
		BeamStart = L_Origin;
		
		if(LaserHitResult.bBlockingHit)
		{
			// End
			BeamEnd = LaserHitResult.ImpactPoint;
			
			if(LaserHitResult.PhysMaterial.Get() == DesiredPhysicsMaterial)
			{
				L_Origin = LaserHitResult.ImpactPoint;
				L_Direction = UKismetMathLibrary::MirrorVectorByNormal(L_Direction,LaserHitResult.ImpactNormal);
				bShouldContinue = true;
			}
			else
			{
				bShouldContinue = false;
			}
		}
		else
		{	// End
			BeamEnd = End;
			bShouldContinue = false;
		}
		K2_SpawnBeam(BeamStart,BeamEnd);
	}
}


