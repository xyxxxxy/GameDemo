// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/SMainAction.h"
#include "SGameMacros.h"
#include "Action/SActionComponent.h"
#include "Components/PostProcessComponent.h"

bool USMainAction::CanStart_Implementation(AActor* Instigator)
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

void USMainAction::StartAction_Implementation(AActor* Instigator)
{
	Super::StartAction_Implementation(Instigator);
}

void USMainAction::StopAction_Implementation(AActor* Instigator)
{
	GetOwningComponent()->SetMainActionDeployed(false);
	if(UPostProcessComponent* Comp=Cast<UPostProcessComponent>
  (Instigator->GetComponentByClass(UPostProcessComponent::StaticClass())))
	{
		Comp->bEnabled=false;
	}
	Super::StopAction_Implementation(Instigator);
}

void USMainAction::K2_StartDeploy_Implementation(USActionComponent* OwningComp, AActor* Instigator)
{
	Super::K2_StartDeploy_Implementation(OwningComp, Instigator);

	if(UPostProcessComponent* Comp=Cast<UPostProcessComponent>
		(Instigator->GetComponentByClass(UPostProcessComponent::StaticClass())))
	{
		Comp->bEnabled=true;
	}
}


bool USMainAction::ShouldStartMainAction(AActor* Instigator)
{
	return true;
}

void USMainAction::UpdateMaterials(TArray<AStaticMeshActor*> Actors, bool bIsToDeploy)
{
}
