// Fill out your copyright notice in the Description page of Project Settings.

#include "Action/SMainAction_NoCollision.h"
#include "Action/SActionComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "SGameCharacter.h"
#include "SNoCollisionActor.h"
#include "SNoCollisionComponent.h"


bool USMainAction_NoCollision::IsValidTime() const
{
	return bIsValidTime;
}

void USMainAction_NoCollision::TimerCallBack()
{
	bIsValidTime=true;
	HitActor=nullptr;
}



bool USMainAction_NoCollision::UpdateSingleMaterial(AActor* SingleActor, UMaterialInstance* NewMaterial)
{
	if(!SingleActor)
	{
		return false;
	}
	if(	UStaticMeshComponent* Comp=Cast<UStaticMeshComponent>
	(SingleActor->GetComponentByClass(UStaticMeshComponent::StaticClass())))
	{
		int32 MaterialNum=Comp->GetNumMaterials();
		for(int32 i=0;i<MaterialNum;++i)
		{
			Comp->SetMaterial(i,NewMaterial);
		}
		return true;
	}
	return false;
	
}

bool USMainAction_NoCollision::EliminateCollisionTrace(AActor* Instigator)
{
	if(ASGameCharacter* Player=Cast<ASGameCharacter>(Instigator))
	{
		FVector Start =Player->GetFollowCamera()->GetComponentLocation();
		FVector End = Start+Player->GetFollowCamera()->GetForwardVector() * TraceDistance;
		FHitResult HitResult;
		
		GetWorld()->LineTraceSingleByChannel(HitResult,Start,End,CollisionChannel);
		
		if(!HitResult.bBlockingHit ||
			(HitResult.bBlockingHit && !HitResult.GetActor()->ActorHasTag(AbilityTag)))
		{
			return false;
		}
		AActor* Actor=HitResult.GetActor();
		if(Actor == HitActor)
		{
			return true;
		}
		HitActor=HitResult.GetActor();
		return true;
	}
	return false;
}


void USMainAction_NoCollision::StartAction_Implementation(AActor* Instigator)
{
	if(!IsValidTime())
	{
		return;
	}
	Super::StartAction_Implementation(Instigator);

	if(EliminateCollisionTrace(Instigator))
	{
		bIsValidTime=false;
		if(USNoCollisionComponent* Comp = Cast<USNoCollisionComponent>
			(HitActor->GetComponentByClass(USNoCollisionComponent::StaticClass())))
		{
			if(Comp->Implements<USActionInterface>())
			{
				Comp->OnEffectEnd.AddDynamic(this,&USMainAction_NoCollision::TimerCallBack);
				StopAction_Implementation(Instigator);
				Execute_ActionInteract(Comp,Instigator);
			}
		}
	}
	else
	{
		GetOwningComponent()->OnMainActionStartDeployed.Broadcast(GetOwningComponent(),Instigator);
	}
}


void USMainAction_NoCollision::TraceInspection_Implementation(AActor* InstigatorActor)
{
	Super::TraceInspection_Implementation(InstigatorActor);
	if(!IsValidTime())
	{
		return;
	}
	if(ASGameCharacter* Player=Cast<ASGameCharacter>(InstigatorActor))
	{
		FVector Start =Player->GetFollowCamera()->GetComponentLocation();
		FVector End = Start+Player->GetFollowCamera()->GetForwardVector() * TraceDistance;
		FHitResult HitResult;
		
		GetWorld()->LineTraceSingleByChannel(HitResult,Start,End,CollisionChannel);
		
		if(CShowActionTrace.GetValueOnAnyThread())
		{
			const FColor Color=HitResult.bBlockingHit?FColor::Green:FColor::Red;
			DrawDebugLine(GetWorld(),Start,End,Color,false,0.1f);
		}
		
		if(!HitResult.bBlockingHit ||
			(HitResult.bBlockingHit && !HitResult.GetActor()->ActorHasTag(AbilityTag)))
		{
			UpdateSingleMaterial(HitActor,DeployedMaterial);
			HitActor=nullptr;
			return;
		}
		
		AActor* Actor=HitResult.GetActor();
		if(Actor == HitActor)
		{
			return;
		}
		UpdateSingleMaterial(HitActor,DeployedMaterial);
		UpdateSingleMaterial(Actor,SelectedMaterial);
		HitActor=Actor;
		
	}
}

bool USMainAction_NoCollision::ShouldStartMainAction(AActor* Instigator)
{
	return IsValidTime();
}

void USMainAction_NoCollision::UpdateMaterialsByNoCollision(TArray<AActor*> Actors, bool bIsToDeploy)
{
	
	for(AActor* Actor:Actors)
	{
		if(UStaticMeshComponent* Comp=Cast<UStaticMeshComponent>
	(Actor->GetComponentByClass(UStaticMeshComponent::StaticClass())))
		{
			int32 MaterialNum = Comp->GetNumMaterials();
			//DISPLAY_SCREEN(FString("Mat NUm: ").Append(FString::FromInt(MaterialNum)));
			TArray<UMaterialInterface*> Materials = Comp->GetMaterials();
			for(int32 i=0;i<MaterialNum;++i)
			{
				if(bIsToDeploy)
				{
					Comp->SetMaterial(i,DeployedMaterial);
				}
				else
				{
					Comp->SetMaterial(i,nullptr);
				}
			}
		}
	}
}
