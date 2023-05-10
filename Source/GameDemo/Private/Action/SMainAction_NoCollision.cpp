// Fill out your copyright notice in the Description page of Project Settings.

#include "Action/SMainAction_NoCollision.h"
#include "Action/SActionComponent.h"
#include "Camera/CameraComponent.h"
#include "DrawDebugHelpers.h"
#include "SGameCharacter.h"
#include "SGameMacros.h"
#include "Engine/StaticMeshActor.h"


void USMainAction_NoCollision::RecoverMaterial(AActor* Instigator)
{
	bIsValidTime=true;
	if(GetOwningComponent()->IsMainActionDeployed())
	{
		GetOwningComponent()->OnMainActionStartDeployed.Broadcast(GetOwningComponent(),Instigator);
		DISPLAY_LOG(TEXT("recover to deploy material!"));
	}
	else
	{
		UpdateSingleMaterial(HitComponent,nullptr);
	}
	HitComponent->SetCollisionProfileName("BlockAll");
	HitComponent=nullptr;
	ClearRecoverTimer();
}

bool USMainAction_NoCollision::IsValidTime() const
{
	return bIsValidTime;
}

void USMainAction_NoCollision::ClearRecoverTimer()
{
	DISPLAY_LOG(TEXT("Clear TimerHandle!"));
	GetWorld()->GetTimerManager().ClearTimer(RecoverTimer);
}

bool USMainAction_NoCollision::UpdateSingleMaterial(UPrimitiveComponent* PrimitiveComp, UMaterialInstance* NewMaterial)
{
	if(!PrimitiveComp)
	{
		return false;
	}
	int32 TotalNumMaterial=PrimitiveComp->GetNumMaterials();
	for(int32 i=0;i<TotalNumMaterial;++i)
	{
		PrimitiveComp->SetMaterial(i,NewMaterial);
	}
	
	return true;
	
}

bool USMainAction_NoCollision::EliminateCollisionTrace(AActor* Instigator)
{
	if(ASGameCharacter* Player=Cast<ASGameCharacter>(Instigator))
	{
		FVector Start =Player->GetFollowCamera()->GetComponentLocation();
		FVector End = Start+Player->GetFollowCamera()->GetForwardVector() * TraceDistance;
		FHitResult HitResult;
		FCollisionQueryParams QueryParams;
		QueryParams.bReturnPhysicalMaterial=true;
		GetWorld()->LineTraceSingleByChannel(HitResult,Start,End,
			ECC_Visibility,QueryParams);
		if(!HitResult.bBlockingHit &&
			(HitResult.bBlockingHit && !HitResult.GetComponent()->ComponentHasTag(AbilityTag)))
		{
			return false;
		}
		UPrimitiveComponent* Comp=HitResult.GetComponent();
		if(Comp == HitComponent)
		{
			return true;
		}
		HitComponent=HitResult.GetComponent();
		return true;
	}
	return false;
}
	
	


void USMainAction_NoCollision::SetNoCollisionMaterial(UPrimitiveComponent* PrimitiveComp,AActor* Instigator)
{
	UpdateSingleMaterial(PrimitiveComp,TranslucentMaterial);
	PrimitiveComp->SetCollisionProfileName(NewCollisionName);
}

void USMainAction_NoCollision::InitialVariable()
{
	//HitComponent=nullptr;
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
		RecoverDelegate.BindUFunction(this,"RecoverMaterial",Instigator);
		GetWorld()->GetTimerManager().SetTimer(RecoverTimer,RecoverDelegate,EffectTime,false);
		StopAction_Implementation(Instigator);
		SetNoCollisionMaterial(HitComponent,Instigator);
	}
	else
	{
		GetOwningComponent()->OnMainActionStartDeployed.Broadcast(GetOwningComponent(),Instigator);
	}
}



void USMainAction_NoCollision::TraceInspection_Implementation(AActor* Instigator)
{
	Super::TraceInspection_Implementation(Instigator);
	if(!IsValidTime())
	{
		return;
	}
	if(ASGameCharacter* Player=Cast<ASGameCharacter>(Instigator))
	{
		FVector Start =Player->GetFollowCamera()->GetComponentLocation();
		FVector End = Start+Player->GetFollowCamera()->GetForwardVector() * TraceDistance;
		FHitResult HitResult;
		FCollisionQueryParams QueryParams;
		QueryParams.bReturnPhysicalMaterial=true;
		GetWorld()->LineTraceSingleByChannel(HitResult,Start,End,
			ECC_Visibility,QueryParams);
		if(CShowActionTrace.GetValueOnAnyThread())
		{
			const FColor Color=HitResult.bBlockingHit?FColor::Green:FColor::Red;
			DrawDebugLine(GetWorld(),Start,End,Color,false,0.1f);
		}
		
		if(!HitResult.bBlockingHit ||
			(HitResult.bBlockingHit && !HitResult.GetComponent()->ComponentHasTag(AbilityTag)))
		{
			UpdateSingleMaterial(HitComponent,DeployedMaterial);
			HitComponent=nullptr;
			return;
		}
		UPrimitiveComponent* Comp=HitResult.GetComponent();

		if(Comp == HitComponent)
		{
			return;
		}
		UpdateSingleMaterial(HitComponent,DeployedMaterial);
		UpdateSingleMaterial(Comp,SelectedMaterial);
		HitComponent=Comp;
		
	}
}

bool USMainAction_NoCollision::ShouldStartMainAction(AActor* Instigator)
{
	return IsValidTime();
}

void USMainAction_NoCollision::UpdateMaterials(TArray<AStaticMeshActor*> Actors, bool bIsToDeploy)
{
	for(AStaticMeshActor* Actor:Actors)
	{
		
		UStaticMeshComponent* Comp=Actor->GetStaticMeshComponent();
		int32 TotalNumMaterials= Comp->GetNumMaterials();
		TArray<UMaterialInterface*> Materials= Comp->GetMaterials();
		for(int32 MaterialIndex=0;MaterialIndex<TotalNumMaterials;++MaterialIndex)
		{
				if(bIsToDeploy)
				{
					Comp->SetMaterial(MaterialIndex,DeployedMaterial);
				}
				else
				{
					Comp->SetMaterial(MaterialIndex,nullptr);
				}

				DISPLAY_LOG(TEXT("Materials has set!"));
			
		}
	}
}
