// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/SActionComponent.h"

#include "Action/SAction.h"
#include "SGameMacros.h"


USActionComponent::USActionComponent()
{
	
	PrimaryComponentTick.bCanEverTick=true;
	
	MainActionsName = "MainAction";
}



void USActionComponent::BeginPlay()
{
	Super::BeginPlay();
	SetComponentTickEnabled(false);
	for(const TSubclassOf<USAction> ActionClass:DefaultActions)
	{
		AddAction(GetOwner(),ActionClass);
	}
	for(const TSubclassOf<USAction> ActionClass:DefaultMainActions)
	{
		AddAction(GetOwner(),ActionClass);
	}
	if(DefaultMainActions.Num()>0)
	{
		CurrentMainAction=Actions[DefaultActions.Num()];
	}
}

void USActionComponent::ActionTraceCheck()
{
	if(CurrentMainAction && CurrentMainAction->Implements<USActionInterface>())
	{
		CurrentMainAction->TraceInspection_Implementation(GetOwner());
	}
}

void USActionComponent::AddAction(AActor* Instigator, TSubclassOf<USAction> ActionClass)
{
	if(!ensure(ActionClass))
	{
		return;
	}
	for(USAction* Action:Actions)
	{
		if(ActionClass == Action->GetClass())
		{
			return;
		}
	}
	USAction* NewAction=NewObject<USAction>(this,ActionClass);
	if(ensure(NewAction))
	{
		Actions.Add(NewAction);
		OnMainActionStartDeployed.AddDynamic(NewAction,&USAction::K2_StartDeploy);
		OnMainActionEndDeployed.AddDynamic(NewAction,&USAction::K2_EndDeploy);
		
		if(NewAction->ActionName==MainActionsName)
		{
			if(CurrentMainAction!=NewAction)
			{
				CurrentMainAction=NewAction;
			}
		}
	}

	
}

bool USActionComponent::StartActionByName(AActor* Instigator,FName Name)
{
	if(Name == MainActionsName)
	{
		if(CurrentMainAction && CurrentMainAction->CanStart(Instigator))
		{
			CurrentMainAction->StartAction(Instigator);
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
		if(CurrentMainAction && CurrentMainAction->IsRunning())
		{
			CurrentMainAction->StopAction(Instigator);
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
	
	if(CurrentMainAction->GetClass() == ActionSwitchTo)
	{
		DISPLAY_LOG(TEXT("Switch Equal!"));
		return;
	}
	for(USAction* Action : Actions)
	{
		if(ActionSwitchTo == Action->GetClass())
		{
			DISPLAY_LOG(TEXT("Success to Switch!"));
			CurrentMainAction = Action;
		}
	}

}

bool USActionComponent::IsMainActionDeployed() const
{
	return bIsMainActionDeployed;
}

void USActionComponent::SetMainActionDeployed(bool NewState)
{
	bIsMainActionDeployed=NewState;
	if(bIsMainActionDeployed)
	{
		OnMainActionStartDeployed.Broadcast(this,GetOwner());
	}
	else
	{
		OnMainActionEndDeployed.Broadcast(this,GetOwner());
	}
}

void USActionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	ActionTraceCheck();
}

bool USActionComponent::HaveMainAction() const
{
	if(CurrentMainAction)
	{
		return true;
	}
	return false;
}






