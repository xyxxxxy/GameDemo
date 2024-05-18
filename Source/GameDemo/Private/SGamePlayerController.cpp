
#include "SGamePlayerController.h"
#include "Blueprint/UserWidget.h"
#include "SGameMacros.h"
#include "UGameBlueprintFunctionLibrary.h"
#include "Action/SActionComponent.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"
#include "Framework/Application/NavigationConfig.h"
#include "GameFramework/Character.h"

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

void ASGamePlayerController::OpenActionMenu()
{
	if(USActionComponent* Comp = Cast<USActionComponent>
		(GetCharacter()->GetComponentByClass(USActionComponent::StaticClass())))
	{
		if(Comp->IsMainActionDeployed() || !Comp->HaveMainAction())
		{
			return;
		}
	}
	
	if(ensure(ActionMenuClass))
	{
		ActionMenuInstance = CreateWidget<UUserWidget>(this, ActionMenuClass);
		if(ActionMenuInstance)
		{
			ActionMenuInstance->AddToViewport();
			SetShowMouseCursor(false);
			UGameBlueprintFunctionLibrary::ControlPlayerInput(GetWorld(),false);
		}
	}
}

void ASGamePlayerController::CloseActionMenu()
{
	DISPLAY_LOG(TEXT("Close Action Menu!"));
	if(ActionMenuInstance && ActionMenuInstance->IsInViewport())
	{
		if(ActionMenuInstance->Implements<USUIManagerInterface>())
		{
			Execute_CloseUI(ActionMenuInstance);
		}
	}
}


void ASGamePlayerController::CreateMainWidget()
{
	DISPLAY_LOG(TEXT("PC CreateMainWidget!"));
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
	InputComponent->BindAction("SwitchAction",IE_Pressed,this,&ASGamePlayerController::OpenActionMenu);
	InputComponent->BindAction("SwitchAction",IE_Released,this,&ASGamePlayerController::CloseActionMenu);
}

void ASGamePlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(IsLocalController())
	{
		auto Navigation = MakeShared<FNavigationConfig>();
		Navigation->bTabNavigation = false;
		FSlateApplication::Get().SetNavigationConfig(Navigation);
	}
}












