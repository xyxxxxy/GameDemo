// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/SWidget_Action.h"

#include "SGamePlayerState.h"
#include "Action/SAction.h"


void USWidget_Action::SwitchAction_Implementation(USAction* OldAction, USAction* NewAction,FSActionProperty Property)
{
	ActionProperty = Property;
	GetActionProperty();
}

void USWidget_Action::NativeConstruct()
{
	Super::NativeConstruct();

	if(ASGamePlayerState* PS = Cast<ASGamePlayerState>(GetOwningPlayerState()))
	{
		PS->OnActionSWitchedForPS.AddDynamic(this,&USWidget_Action::SwitchAction);
		
	}
	
}

void USWidget_Action::GetActionProperty()
{
	if(ASGamePlayerState* PS = Cast<ASGamePlayerState>(GetOwningPlayerState()))
	{
		if(PS->HaveCurrentMainAction())
		{
			ActionProperty = PS->GetActionProperty(PS->GetCurrentMainAction()->ActionName);
			ActionName = ActionProperty.ActionName;
			IconBrush = ActionProperty.ActionBrush;
		}
	}
}
