// Fill out your copyright notice in the Description page of Project Settings.


#include "SWorldWidget_Interaction.h"
#include "SInteractActor.h"

void USWorldWidget_Interaction::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	SetUILocation();
	
}

void USWorldWidget_Interaction::SetTextName()
{
	if(!IsValid(AttachedActor))
	{
		return;
	}
	
	if(ASInteractActor* Actor = Cast<ASInteractActor>(AttachedActor))
	{
		if(Actor->Implements<USInteractInterface>())
		{
			Actor->GetCategory_Implementation(TextName);
		}
	}
}
