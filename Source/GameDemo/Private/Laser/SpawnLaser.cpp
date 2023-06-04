// Fill out your copyright notice in the Description page of Project Settings.


#include "Laser/SpawnLaser.h"
#include "Components/ArrowComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Laser/SLaserInterface.h"


ASpawnLaser::ASpawnLaser()
{
	PrimaryActorTick.bCanEverTick = true;
	
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	RootComponent = StaticMeshComp;

	BeamArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("BeamArrow"));
	BeamArrow->SetupAttachment(StaticMeshComp);
}


void ASpawnLaser::ClearBeams()
{
	for(AActor* Actor : BeamActors)
	{
		Actor->Destroy();
	}
	BeamActors.Empty();
}

void ASpawnLaser::CastLight(FVector Origin, FVector Direction, float Distance)
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
		AActor* HitActor = LaserHitResult.GetActor();
		if(HitActor)
		{
			if(HitActor->Implements<USLaserInterface>())
			{
				ISLaserInterface::Execute_LaserInteract(HitActor,this,true);
			}
		}
		K2_SpawnBeam(BeamStart,BeamEnd);
	}
}


