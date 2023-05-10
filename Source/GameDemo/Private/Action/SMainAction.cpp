// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/SMainAction.h"
#include "SGameMacros.h"
#include "Action/SActionComponent.h"

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
	Super::StopAction_Implementation(Instigator);
}

bool USMainAction::ShouldStartMainAction(AActor* Instigator)
{
	return true;
}

void USMainAction::UpdateMaterials(TArray<AStaticMeshActor*> Actors, bool bIsToDeploy)
{
}
