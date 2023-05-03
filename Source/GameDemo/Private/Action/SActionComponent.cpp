// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/SActionComponent.h"

#include "Action/SAction.h"


USActionComponent::USActionComponent()
{

	PrimaryComponentTick.bCanEverTick = true;
	MainActionsName = "MainAction";
}



void USActionComponent::BeginPlay()
{
	Super::BeginPlay();

	for(const TSubclassOf<USAction> ActionClass:DefaultActions)
	{
		AddAction(GetOwner(),ActionClass);
	}
	
}

void USActionComponent::AddAction(AActor* Instigator, TSubclassOf<USAction> ActionClass)
{
	if(!ensure(ActionClass))
	{
		return;
	}
	USAction* NewAction=NewObject<USAction>(this,ActionClass);
	if(ensure(NewAction))
	{
		Actions.Add(NewAction);
	}
	
}

bool USActionComponent::StartActionByName(AActor* Instigator,FName Name)
{
	if(Name == MainActionsName)
	{
		if(MainActions && MainActions->CanStart(Instigator))
		{
			MainActions->StartAction(Instigator);
			return true;
		}
	}
	for(USAction* Action : Actions)
	{
		if(Action->ActionName == Name && Action->CanStart(Instigator))
		{
			Action->StartAction(Instigator);
			return true;
		}
	}
	return false;
}

bool USActionComponent::StopActionByName(AActor* Instigator,FName Name)
{
	if(Name == MainActionsName)
	{
		if(MainActions && MainActions->IsRunning())
		{
			MainActions->StopAction(Instigator);
			return true;
		}
	}
	for(USAction* Action : Actions)
	{
		if(Action->ActionName == Name && Action->IsRunning())
		{
			Action->StopAction(Instigator);
			return true;
		}
	}
	return false;
}

void USActionComponent::RemoveAction(AActor* Instigator, USAction* ActionToRemove)
{
	if(!ensure(ActionToRemove && !ActionToRemove->IsRunning()))
	{
		return;
	}
	Actions.Remove(ActionToRemove);
}

void USActionComponent::SwitchMainAction(AActor* Instigator, TSubclassOf<USAction> ActionSwitchTo)
{
	if(MainActions->GetClass() == ActionSwitchTo)
	{
		return;
	}
	for(USAction* Action : Actions)
	{
		if(Action->GetClass() == ActionSwitchTo)
		{
			MainActions = Action;
		}
	}

}

bool USActionComponent::IsMainActionDeployed() const
{
	return bIsMainActionDeployed;
}

void USActionComponent::SetMainActionDeployed(bool NewState)
{
	if(NewState != bIsMainActionDeployed)
	{
		bIsMainActionDeployed=NewState;
	}
}






