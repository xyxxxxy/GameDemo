// Fill out your copyright notice in the Description page of Project Settings.


#include "Action/SActionInterface.h"
#include "SGameMacros.h"

void ISActionInterface::TraceInspection_Implementation(AActor* InstigatorActor)
{
	//DISPLAY_LOG(TEXT("Action Trace!"));
}

void ISActionInterface::ActionInteract_Implementation(AActor* InstigatorActor)
{
	DISPLAY_LOG(TEXT("Action Interact!"));
}
