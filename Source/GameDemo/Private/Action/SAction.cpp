// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/SAction.h"

#include "Action/SActionComponent.h"
#include "SGameMacros.h"

USActionComponent* USAction::GetOwningComponent() const
{
	return Cast<USActionComponent>(GetOuter());
}

UWorld* USAction::GetWorld() const
{
	if(const USActionComponent* Comp=GetOwningComponent())
	{
		return Comp->GetWorld();
	}
	return nullptr;
}

bool USAction::IsRunning() const
{
	return bIsRunning;
}

bool USAction::CanStart_Implementation(AActor* Instigator)
{
	if(IsRunning())
	{
		return false;
	}
	if(const USActionComponent* Comp=GetOwningComponent())
	{
		if(Comp->ActiveTag.HasAny(BlockedTags))
		{
			return false;
		}
	}
	return true;
	
}

void USAction::StartAction_Implementation(AActor* Instigator)
{

	DISPLAY_LOG(FString("Running : ").Append(GetNameSafe(this)));
	if(USActionComponent* Comp=GetOwningComponent())
	{
		Comp->ActiveTag.AppendTags(GrantTags);
		bIsRunning=true;
		Comp->OnActionStarted.Broadcast(Comp,this);
	}
}

void USAction::StopAction_Implementation(AActor* Instigator)
{
	DISPLAY_LOG(FString("Stop : ").Append(GetNameSafe(this)));
	ensureAlways(bIsRunning);
	if(USActionComponent* Comp=GetOwningComponent())
	{
		Comp->ActiveTag.RemoveTags(GrantTags);
		bIsRunning=false;
		Comp->OnActionStopped.Broadcast(Comp,this);
	}
}




