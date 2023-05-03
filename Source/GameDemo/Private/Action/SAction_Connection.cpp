// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/SAction_Connection.h"

#include "DrawDebugHelpers.h"
#include "SGameCharacter.h"
#include "Action/SActionComponent.h"
#include "SGameMacros.h"
#include "Camera/CameraComponent.h"

static TAutoConsoleVariable<bool> CShowTrace(TEXT("Action.ShowTrace"),true,
	TEXT("Enable Show Trace."),ECVF_Cheat);

bool USAction_Connection::CanStart_Implementation(AActor* Instigator)
{

	if(const USActionComponent* Comp=GetOwningComponent())
	{
		if(Comp->ActiveTag.HasAny(BlockedTags))
		{
			return false;
		}
	}
	DISPLAY_LOG(FString("Can Start : ").Append(GetNameSafe(this)));
	return true;
}

void USAction_Connection::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	if(!bIsStartSet)
	{
		FirstTrace(Instigator);
		
	}
	else
	{
		SecondTrace(Instigator);
		K2_SpawnConnections();
		Super::StopAction_Implementation(Instigator);
	}
}

void USAction_Connection::ValReset()
{
	Super::ValReset();

	bIsStartSet=false;
	HitComponent=nullptr;
	FirstLocation=FVector::ZeroVector;
	SecondLocation=FVector::ZeroVector;
}

void USAction_Connection::FirstTrace(AActor* Instigator)
{
	if(ASGameCharacter* Player=Cast<ASGameCharacter>(Instigator))
	{
		FVector Start =Player->GetFollowCamera()->GetComponentLocation();
		FVector End = Start+Player->GetFollowCamera()->GetForwardVector() * TraceDistance;
		FHitResult HitResult;
		FCollisionQueryParams QueryParams;
		QueryParams.bTraceComplex=true;
		QueryParams.bReturnPhysicalMaterial=true;
		GetWorld()->LineTraceSingleByChannel(HitResult,Start,End,
			ECC_Visibility,QueryParams);
		
		if(CShowTrace.GetValueOnAnyThread())
		{
			const FColor Color=HitResult.bBlockingHit?FColor::Green:FColor::Red;
			DrawDebugLine(GetWorld(),Start,End,Color,false,2.0f);
		}
		
		if(HitResult.bBlockingHit)
		{
			if(HitResult.PhysMaterial.Get() == ConnectionMaterial)
			{
				HitComponent=HitResult.GetComponent();
				FirstLocation=HitResult.Location;
				bIsStartSet=true;
				DISPLAY_LOG(FString("First : ").Append(GetNameSafe(this)));
			}
		}
	}
}

void USAction_Connection::SecondTrace(AActor* Instigator)
{
	if(ASGameCharacter* Player=Cast<ASGameCharacter>(Instigator))
	{
		FVector Start =Player->GetFollowCamera()->GetComponentLocation();
		FVector End = Start+Player->GetFollowCamera()->GetForwardVector() * TraceDistance;
		FHitResult HitResult;
		FCollisionQueryParams QueryParams;
		QueryParams.bTraceComplex=true;
		QueryParams.bReturnPhysicalMaterial=true;
		GetWorld()->LineTraceSingleByChannel(HitResult,Start,End,
			ECC_Visibility,QueryParams);
		
		if(CShowTrace.GetValueOnAnyThread())
		{
			const FColor Color=HitResult.bBlockingHit?FColor::Green:FColor::Red;
			DrawDebugLine(GetWorld(),Start,End,Color,false,2.0f);
		}
		if(HitResult.bBlockingHit)
		{
			if(HitResult.PhysMaterial.Get() == ConnectionMaterial && HitResult.GetComponent() !=HitComponent)
			{
				SecondLocation=HitResult.Location;
				HitComponent=nullptr;
				bIsStartSet=false;
				DISPLAY_LOG(FString("Second : ").Append(GetNameSafe(this)));
			}

		}
	}
}




