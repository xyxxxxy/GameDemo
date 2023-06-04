// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/SMainAction_Laser.h"

#include "SGameCharacter.h"
#include "DrawDebugHelpers.h"
#include "SGameMacros.h"
#include "Action/SActionComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Laser/SLaserSensorInterface.h"

void USMainAction_Laser::CastLight(AActor* InstigatorActor,FVector HandOrigin, FVector Origin, FVector Direction,float Distance)
{
	FVector L_Origin = Origin;
	FVector L_Direction = Direction;
	FVector L_HandOrigin = HandOrigin;
	float L_Distance = Distance;

	FVector BeamStart;

	ClearBeams();
	
	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.bTraceComplex = true;
	QueryParams.bReturnPhysicalMaterial = true;
	QueryParams.AddIgnoredActor(InstigatorActor);
	FVector End = L_Origin + L_Direction * FirstDistance;

	// first trace
	GetWorld()->LineTraceSingleByChannel(HitResult,L_Origin,
		End,CollisionChannel,QueryParams);
	
	if(!HitResult.bBlockingHit)
	{
		K2_SpawnBeam(L_HandOrigin,End);
		if(HitActor)
		{
			if(HitActor->Implements<USLaserSensorInterface>())
			{
				ISLaserSensorInterface::Execute_SetState(HitActor,InstigatorActor,false);
			}
			HitActor = nullptr;
		}
		bIsReflect = false;
		return;
	}
	if(HitActor && HitActor != HitResult.GetActor())
	{
		if(HitActor->Implements<USLaserSensorInterface>())
		{
			ISLaserSensorInterface::Execute_SetState(HitActor,InstigatorActor,false);
		}
		HitActor = nullptr;
	}
	
	
	L_Direction = HitResult.Location - L_HandOrigin;
	L_Origin = L_HandOrigin;
	L_Direction = L_Direction.GetSafeNormal();
	
	bool bShouldContinue = true;

	int32 BeamNumbers = 0;

	// loop
	while(bShouldContinue && BeamNumbers < MaxBeamNumber)
	{
		FHitResult LaserHitResult;
		
		End = L_Origin + L_Direction * L_Distance;
		
		GetWorld()->LineTraceSingleByChannel(LaserHitResult,L_Origin,
			End,CollisionChannel,QueryParams);
		
		if(CShowActionTrace.GetValueOnAnyThread())
		{
			DrawDebugLine(GetWorld(),L_Origin,End,FColor::Red,false,0.1f);
		}
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
		
		HitActor = HitResult.GetActor();
		if(HitActor)
		{
			if(HitActor->Implements<USLaserSensorInterface>())
			{
				ISLaserSensorInterface::Execute_SetState(HitActor,InstigatorActor,true);
				break;
			}
		}
		bIsReflect = true;
		BeamNumbers++;
	}
}

void USMainAction_Laser::ClearBeams()
{
	for(AActor* Actor : BeamActors)
	{
		Actor->Destroy();
	}
	BeamActors.Empty();
}

bool USMainAction_Laser::IsReflect() const
{
	return bIsReflect;
}

void USMainAction_Laser::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);
}

void USMainAction_Laser::TraceInspection_Implementation(AActor* InstigatorActor)
{
	Super::TraceInspection_Implementation(InstigatorActor);
	
	if(ASGameCharacter* Player = Cast<ASGameCharacter>(InstigatorActor))
	{
		CastLight(InstigatorActor,Player->GetMesh()->GetSocketLocation(BoneName),
			Player->GetFollowCamera()->GetComponentLocation(),
			Player->GetFollowCamera()->GetForwardVector(),LaserDistance);
	}
}

void USMainAction_Laser::K2_StartDeploy_Implementation(USActionComponent* OwningComp, AActor* Instigator)
{
	Super::K2_StartDeploy_Implementation(OwningComp, Instigator);

	GetOwningComponent()->SetComponentTickInterval(0.01f);
}

void USMainAction_Laser::InitialVariable()
{
	ClearBeams();
	if(HitActor)
	{
		if(HitActor->Implements<USLaserSensorInterface>())
		{
			ISLaserSensorInterface::Execute_SetState(HitActor,GetOwningComponent()->GetOwner(),false);
			DISPLAY_LOG(FString("LaserSensor : False!"));
		}
		HitActor = nullptr;
	}
	HitActor = nullptr;
	bIsReflect = false;
}

void USMainAction_Laser::StopAction_Implementation(AActor* Instigator)
{
	Super::StopAction_Implementation(Instigator);

	GetOwningComponent()->SetComponentTickInterval(0.0f);
	
}





