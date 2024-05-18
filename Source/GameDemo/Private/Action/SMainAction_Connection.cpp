// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/SMainAction_Connection.h"

#include "DrawDebugHelpers.h"
#include "SGameCharacter.h"
#include "Action/SActionComponent.h"
#include "SGameMacros.h"
#include "SNoCollisionActor.h"
#include "SNoCollisionComponent.h"
#include "Camera/CameraComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"



void USMainAction_Connection::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);

	if(!bIsFirstTraceSet)
	{
		FirstTrace(Instigator);
	}
	else
	{
		SecondTrace(Instigator);
		if(!HasObstacle(Instigator))
		{
			K2_SpawnConnections();
			StopAction_Implementation(Instigator);
		}
		else
		{
			GetOwningComponent()->OnMainActionStartDeployed.Broadcast(GetOwningComponent(),Instigator);
		}
	}
}



void USMainAction_Connection::TraceInspection_Implementation(AActor* InstigatorActor)
{
	Super::TraceInspection_Implementation(InstigatorActor);

	ProbeNoCollision(InstigatorActor);
	
	if(ASGameCharacter* Player=Cast<ASGameCharacter>(InstigatorActor))
	{
		FVector Start =Player->GetFollowCamera()->GetComponentLocation();
		FVector End = Start+Player->GetFollowCamera()->GetForwardVector() * CurrentTraceDistance;
		FHitResult HitResult;
		FCollisionQueryParams QueryParams;
		QueryParams.bTraceComplex=true;
		QueryParams.bReturnPhysicalMaterial=true;
		GetWorld()->LineTraceSingleByChannel(HitResult,Start,End,
			ECC_Visibility,QueryParams);
		
		if(CShowActionTrace.GetValueOnAnyThread())
		{
			const FColor Color=HitResult.bBlockingHit?FColor::Green:FColor::Red;
			DrawDebugLine(GetWorld(),Start,End,Color,false,0.1f);
		}
		
		if(HitResult.bBlockingHit)
		{
			UPrimitiveComponent* Comp=HitResult.GetComponent();
			if(HitResult.PhysMaterial.Get() == DesiredPhysicsMaterial)
			{
				int32 CurrentSectionIndex;
				Comp->GetMaterialFromCollisionFaceIndex(HitResult.FaceIndex,CurrentSectionIndex);
				
				if(!TraceComponent)
				{
					TraceComponent=Comp;
				}
				if(CurrentSectionIndex == PreSectionIndex && Comp==TraceComponent)
				{
					return;
				}
				if((Comp!=TraceComponent) ||
					(CurrentSectionIndex!=PreSectionIndex && Comp==TraceComponent))
				{
					UpdateSingleMaterial(PreSectionIndex,Comp,DeployedMaterial);
					UpdateSingleMaterial(CurrentSectionIndex,Comp,SelectedMaterial);
					TraceComponent=Comp;
					PreSectionIndex=CurrentSectionIndex;
					return;
				}
			}
			else
			{
				UpdateSingleMaterial(PreSectionIndex,TraceComponent,DeployedMaterial);
				PreSectionIndex=-1;
				TraceComponent=nullptr;
				return;
			}
		}
		else
		{
			UpdateSingleMaterial(PreSectionIndex,TraceComponent,DeployedMaterial);
			PreSectionIndex=-1;
			TraceComponent=nullptr;
			return;
		}
	}
}

void USMainAction_Connection::UpdateMaterials(TArray<AStaticMeshActor*> Actors,bool bIsToDeploy)
{
	for(AStaticMeshActor* Actor:Actors)
	{
		UStaticMeshComponent* Comp=Actor->GetStaticMeshComponent();
		int32 TotalNumMaterials= Comp->GetNumMaterials();
		TArray<UMaterialInterface*> Materials= Comp->GetMaterials();
		for(int32 MaterialIndex=0;MaterialIndex<TotalNumMaterials;++MaterialIndex)
		{
			if(Materials[MaterialIndex]->GetPhysicalMaterial() == DesiredPhysicsMaterial)
			{
				if(bIsToDeploy)
				{
					Comp->SetMaterial(MaterialIndex,DeployedMaterial);
				}
				else
				{
					Comp->SetMaterial(MaterialIndex,NormalMaterial);
				}
			}
		}
	}
}

void USMainAction_Connection::FirstTrace(AActor* Instigator)
{
	if(ASGameCharacter* Player=Cast<ASGameCharacter>(Instigator))
	{
		FVector Start =Player->GetFollowCamera()->GetComponentLocation();
		FVector End = Start+Player->GetFollowCamera()->GetForwardVector() * CurrentTraceDistance;
		FHitResult HitResult;
		FCollisionQueryParams QueryParams;
		QueryParams.bTraceComplex=true;
		QueryParams.bReturnPhysicalMaterial=true;
		
		GetWorld()->LineTraceSingleByChannel(HitResult,Start,End,
			ECC_Visibility,QueryParams);
		
		if(CShowActionTrace.GetValueOnAnyThread())
		{
			const FColor Color=HitResult.bBlockingHit?FColor::Green:FColor::Red;
			DrawDebugLine(GetWorld(),Start,End,Color,false,2.0f);
		}
		
		if(HitResult.bBlockingHit)
		{
			if(IsConnectionClass(HitResult))
			{
				return;
			}
			if(HitResult.PhysMaterial.Get() == DesiredPhysicsMaterial)
			{
				HitComponent=HitResult.GetComponent();
				FirstComponent=HitComponent;
				FirstComponent->GetMaterialFromCollisionFaceIndex(HitResult.FaceIndex,FirstSectionIndex);
				FirstActor=HitResult.GetActor();
				FirstLocation=HitResult.Location;
				if(ensureMsgf(CollisionCue,TEXT("Your Connection CollisionCue?")))
				{
					UGameplayStatics::PlaySoundAtLocation(GetWorld(),CollisionCue,FirstLocation,FRotator::ZeroRotator);
				}
		
				bIsFirstTraceSet=true;
				
				DISPLAY_LOG(FString("First : ").Append(GetNameSafe(this)));
			}
		}
	}
}

void USMainAction_Connection::SecondTrace(AActor* Instigator)
{
	if(ASGameCharacter* Player=Cast<ASGameCharacter>(Instigator))
	{
		FVector Start =Player->GetFollowCamera()->GetComponentLocation();
		FVector End = Start+Player->GetFollowCamera()->GetForwardVector() * CurrentTraceDistance;
		FHitResult HitResult;
		FCollisionQueryParams QueryParams;
		QueryParams.bTraceComplex=true;
		QueryParams.bReturnPhysicalMaterial=true;
		GetWorld()->LineTraceSingleByChannel(HitResult,Start,End,
			ECC_Visibility,QueryParams);
		
		if(CShowActionTrace.GetValueOnAnyThread())
		{
			const FColor Color=HitResult.bBlockingHit?FColor::Green:FColor::Red;
			DrawDebugLine(GetWorld(),Start,End,Color,false,2.0f);
		}
		if(HitResult.bBlockingHit)
		{

			if(HitResult.PhysMaterial.Get() == DesiredPhysicsMaterial && HitResult.GetComponent() !=HitComponent)
			{
		
				HitComponent=nullptr;
				bIsFirstTraceSet=false;
				SecondLocation=HitResult.Location;
				if(ensureMsgf(CollisionCue,TEXT("Your Connection CollisionCue?")))
				{
					UGameplayStatics::PlaySoundAtLocation(GetWorld(),CollisionCue,SecondLocation,FRotator::ZeroRotator);
				}
				DISPLAY_LOG(FString("Second : ").Append(GetNameSafe(this)));
			}
		}
	}
}

bool USMainAction_Connection::HasObstacle(AActor* Instigator)
{
	if(SecondLocation==FVector::ZeroVector)
	{
		return true;
	}
	float Distance=UKismetMathLibrary::VSize(FirstLocation-SecondLocation);

	FHitResult HitResult;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(FirstActor);
	
	GetWorld()->SweepSingleByChannel(HitResult,FirstLocation,SecondLocation,
		FQuat::Identity,ECC_Visibility,FCollisionShape::MakeSphere(SphereRadius),
		QueryParams);

	if(CShowActionTrace.GetValueOnAnyThread())
	{
		const FColor Color=HitResult.bBlockingHit?FColor::Green:FColor::Red;
		DrawDebugSphere(GetWorld(),HitResult.Location,SphereRadius,
			4,Color,false,3.0f);
	}
	if(!HitResult.bBlockingHit)
	{
		return false;
	}
	if(HitResult.GetComponent()->IsSimulatingPhysics())
	{
		return false;
	}
	if(HitResult.bBlockingHit && FMath::Abs(Distance-HitResult.Distance)<=TraceTolerance)
	{
		return false;
	}
	return true;
}

bool USMainAction_Connection::IsValidFace(int32 SectionIndex, UPrimitiveComponent* PrimitiveComp)
{
	if(!PrimitiveComp ||
		SectionIndex == -1 ||
		(PrimitiveComp == FirstComponent) && (SectionIndex == FirstSectionIndex))
	{
		return  false;
	}
	return true;
}

void USMainAction_Connection::InitialVariable()
{
	bIsFirstTraceSet=false;
	HitComponent=nullptr;
	FirstActor=nullptr;
	FirstLocation=FVector::ZeroVector;
	SecondLocation=FVector::ZeroVector;
	PreSectionIndex=-1;
	TraceComponent=nullptr;
	FirstSectionIndex=-1;
	FirstComponent=nullptr;
}

bool USMainAction_Connection::IsConnectionClass(const FHitResult& HitResult) const
{
	if(HitResult.GetActor() && HitResult.GetActor()->GetClass() == DefaultConnectionClass)
	{
		HitResult.GetActor()->Destroy();
		return true;
	}
	return false;
}

void USMainAction_Connection::ProbeNoCollision(AActor* InstigatorActor)
{
	if(ASGameCharacter* Player=Cast<ASGameCharacter>(InstigatorActor))
	{
		FVector Start =Player->GetFollowCamera()->GetComponentLocation();
		FVector End = Start+Player->GetFollowCamera()->GetForwardVector() * TraceDistance;
		FHitResult HitResult;
		
		GetWorld()->LineTraceSingleByChannel(HitResult,Start,End,NoCollisionChannel);
		if(!HitResult.bBlockingHit)
		{
			CurrentTraceDistance=TraceDistance;
			return;
		}
		if(USNoCollisionComponent* CollisionComp = Cast<USNoCollisionComponent>
			(HitResult.GetActor()->GetComponentByClass(USNoCollisionComponent::StaticClass())))
		{
			if(CollisionComp->IsTranslucent())
			{
				CurrentTraceDistance = TraceDistance*TraceMagnification;
			}
			else
			{
				CurrentTraceDistance = TraceDistance;
			}
		}
	}
	else
	{
		CurrentTraceDistance=TraceDistance;
	}

}

bool USMainAction_Connection::UpdateSingleMaterial(int32 SectionIndex, UPrimitiveComponent* PrimitiveComp,
                                                   UMaterialInstance* NewMaterial)
{
	if(IsValidFace(SectionIndex,PrimitiveComp))
	{
		PrimitiveComp->SetMaterial(SectionIndex,NewMaterial);
		return true;
	}
	return false;
}



