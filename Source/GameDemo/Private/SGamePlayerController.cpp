// Fill out your copyright notice in the Description page of Project Settings.


#include "SGamePlayerController.h"
#include "Blueprint/UserWidget.h"
#include "SGameMacros.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "GameFramework/CharacterMovementComponent.h"


void ASGamePlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	
	WidgetDelegate.BindUFunction(this,"CreateMainWidget");
	GetWorld()->GetTimerManager().SetTimer(WidgetTimer,WidgetDelegate,DelayTime,false);
	
}

void ASGamePlayerController::TogglePauseMenu()
{
	DISPLAY_LOG(TEXT("Toggle pause menu!"));
	if(PauseMenuInstance && PauseMenuInstance->IsInViewport())
	{
		PauseMenuInstance->RemoveFromParent();
		PauseMenuInstance = nullptr;
		
		SetPause(false);
		SetShowMouseCursor(false);
		SetInputMode(FInputModeGameOnly());
		return;
	}
	
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
	
	const FSoftObjectPath& SoftObjectPath = PauseMenuClass.ToSoftObjectPath();
	
	StreamableManager.RequestAsyncLoad(SoftObjectPath,[&SoftObjectPath,this]()
	{
		
		UClass* WidgetClass = Cast<UClass>(SoftObjectPath.ResolveObject());
		if(WidgetClass)
		{
			PauseMenuInstance = CreateWidget<UUserWidget>(this, WidgetClass);
			if(PauseMenuInstance)
			{
				PauseMenuInstance->AddToViewport();
				SetPause(true);
				SetShowMouseCursor(true);
				SetInputMode(FInputModeUIOnly());
			}
		}
	},FStreamableManager::DefaultAsyncLoadPriority,false);
	
	
	
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

void ASGamePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("PauseMenu",IE_Pressed,this,&ASGamePlayerController::TogglePauseMenu);
}










