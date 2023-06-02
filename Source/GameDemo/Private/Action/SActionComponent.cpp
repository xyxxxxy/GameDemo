// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/SActionComponent.h"
#include "SGameMacros.h"
#include "SGamePlayerState.h"
#include "Action/SMainAction.h"


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
		if(NewAction->GetActionCategory() == EActionCategory::MainAction)
		{
			MainActions.Add(NewAction);
			// ActionAcquired
			OnMainActionAcquired.Broadcast(this,NewAction);
			
			if(!CurrentMainAction)
			{
				CurrentMainAction = NewAction;
				DISPLAY_LOG(TEXT("Success to Switch!"));
				OnActionSwitched.Broadcast(nullptr,NewAction);
				BindMainActionDeploy();
			}
			SwitchMainAction(Instigator,ActionClass);
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
	if(MainActions.Num() > 0)
	{
		for(USAction* Action : MainActions)
		{
			if(ActionSwitchTo == Action->GetClass())
			{
				DISPLAY_LOG(TEXT("Success to Switch!"));
				UnbindMainActionDeploy();
				OnActionSwitched.Broadcast(CurrentMainAction,Action);
				CurrentMainAction = Action;
				BindMainActionDeploy();
			}
		}
	}
}

bool USActionComponent::IsMainActionDeployed() const
{
	return bIsMainActionDeployed;
}

bool USActionComponent::ShouldStartDeploy(AActor* Instigator)
{
	if(CurrentMainAction)
	{
		if(USMainAction* MainAction=Cast<USMainAction>(CurrentMainAction))
		{
			return MainAction->ShouldStartMainAction(Instigator);
		}
	}
	return false;
}

TArray<USAction*> USActionComponent::GetMainActions() const
{
	return MainActions;
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

USAction* USActionComponent::GetMainAction() const
{
	return HaveMainAction()? CurrentMainAction : nullptr;
}

void USActionComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(CurrentMainAction->CanEnableTick())
	{
		ActionTraceCheck();
	}

}

bool USActionComponent::HaveMainAction() const
{
	if(CurrentMainAction)
	{
		return true;
	}
	return false;
}

void USActionComponent::BindMainActionDeploy()
{
	if(HaveMainAction())
	{
		OnMainActionStartDeployed.AddDynamic(CurrentMainAction,&USAction::K2_StartDeploy);
		OnMainActionEndDeployed.AddDynamic(CurrentMainAction,&USAction::K2_EndDeploy);
		DISPLAY_LOG(TEXT("Bind!"));
	}
}

void USActionComponent::UnbindMainActionDeploy()
{
	if(HaveMainAction())
	{
		OnMainActionStartDeployed.RemoveAll(CurrentMainAction);
		OnMainActionEndDeployed.RemoveAll(CurrentMainAction);
		DISPLAY_LOG(TEXT("Unbind!"));
	}
}

void USActionComponent::StopAllActions()
{
	for(USAction* Action : Actions)
	{
		if(Action->IsRunning())
		{
			Action->StopAction(GetOwner());
		}
	}
}






