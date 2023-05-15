// Fill out your copyright notice in the Description page of Project Settings.


#include "SGamePlayerController.h"
#include "Blueprint/UserWidget.h"
#include "SGameMacros.h"



void ASGamePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	WidgetDelegate.BindUFunction(this,"CreateMainWidget");
	GetWorld()->GetTimerManager().SetTimer(WidgetTimer,WidgetDelegate,DelayTime,false);
	
}




void ASGamePlayerController::CreateMainWidget()
{
	DISPLAY_LOG(TEXT("PC Excute!"));
	if(!MainWidgetInstance && ensure(DefaultMainWidgetClass))
	{
		MainWidgetInstance = CreateWidget<UUserWidget>(this,DefaultMainWidgetClass);
		if(!MainWidgetInstance->IsInViewport())
		{
			MainWidgetInstance->AddToViewport();
		}
	}
	GetWorld()->GetTimerManager().ClearTimer(WidgetTimer);
}










