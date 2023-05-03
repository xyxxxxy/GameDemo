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

void USAction::ValReset()
{
}

bool USAction::CanStart_Implementation(AActor* Instigator)
{
	
	if(IsRunning())
	{
		DISPLAY_LOG(FString("is Running : ").Append(GetNameSafe(this)));
		return false;
	}
	if(const USActionComponent* Comp=GetOwningComponent())
	{
		if(Comp->ActiveTag.HasAny(BlockedTags))
		{
			DISPLAY_LOG(FString("HasBlockedTags : ").Append(GetNameSafe(this)));
			return false;
		}
	}
	DISPLAY_LOG(FString("Can Start : ").Append(GetNameSafe(this)));
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
		ValReset();
		Comp->ActiveTag.RemoveTags(GrantTags);
		bIsRunning=false;
		Comp->OnActionStopped.Broadcast(Comp,this);
	}
}




