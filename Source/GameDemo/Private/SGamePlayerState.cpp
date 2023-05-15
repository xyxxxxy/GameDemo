// Fill out your copyright notice in the Description page of Project Settings.


#include "SGamePlayerState.h"

#include "UGameBlueprintFunctionLibrary.h"
#include "Action/SActionComponent.h"
#include "SGameMacros.h"

void ASGamePlayerState::BeginPlay()
{
	Super::BeginPlay();

	if(USActionComponent* Comp=Cast<USActionComponent>
		(GetPawn()->GetComponentByClass(USActionComponent::StaticClass())))
	{
		Comp->OnMainActionAcquired.AddDynamic(this,&ASGamePlayerState::SetActionProperty);
		Comp->OnActionSwitched.AddDynamic(this,&ASGamePlayerState::SetCurrentMainAction);
		DISPLAY_LOG(TEXT("Player State Add Dynamic!"));
	}
	
}

void ASGamePlayerState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);

	if(ASGamePlayerState* PS = Cast<ASGamePlayerState>(PlayerState))
	{
		PS->SetMainActions(MainActions);
		PS->SetCurrentMainAction(nullptr,CurrentMainAction);
		PS->SetActionProperties(ActionProperties);
	}
}

bool ASGamePlayerState::HaveCurrentMainAction() const
{
	return IsValid(CurrentMainAction)? true :false;
}

USAction* ASGamePlayerState::GetCurrentMainAction() const
{
	return CurrentMainAction;
}

TArray<USAction*> ASGamePlayerState::GetNormalActions() const
{
	return NormalActions;
}

TArray<USAction*> ASGamePlayerState::GetMainActions() const
{
	return MainActions;
}

void ASGamePlayerState::SetActionProperty(USActionComponent* Comp,USAction* NewAction)
{
	bool bIsFound;
	FSActionProperty Property;
	UGameBlueprintFunctionLibrary::FindActionInDataTable(NewAction->ActionName,bIsFound,Property);
	if(bIsFound)
	{
		ActionProperties.Emplace(NewAction->ActionName,Property);
		MainActions.Add(NewAction);
		if(!HaveCurrentMainAction())
		{
			CurrentMainAction = NewAction;
		}
	}
}

void ASGamePlayerState::SetActionProperties(const TMap<FName, FSActionProperty>& NewActionProperties)
{
	ActionProperties = NewActionProperties;
}

FSActionProperty ASGamePlayerState::GetActionProperty(FName ActionName)
{
	if(FSActionProperty* NewActionProperty = ActionProperties.Find(ActionName))
	{
		return *NewActionProperty;
	}
	return FSActionProperty();
}

void ASGamePlayerState::SetMainActions(TArray<USAction*> NewActions)
{
	MainActions = NewActions;
}

void ASGamePlayerState::SetCurrentMainAction(USAction* OldAction, USAction* NewAction)
{
	if(OldAction == NewAction)
	{
		return;
	}
	
	CurrentMainAction = NewAction;

	if(FSActionProperty* NewActionProperty = ActionProperties.Find(NewAction->ActionName))
	{
		OnActionSWitchedForPS.Broadcast(OldAction,NewAction,*NewActionProperty);
	}
}

