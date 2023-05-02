// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractComponent.h"

#include "DrawDebugHelpers.h"
#include "SGameCharacter.h"
#include "SInteractActor.h"
#include "SInteractInterface.h"
#include "SWorldWidget_Interaction.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "SGameMacros.h"

static TAutoConsoleVariable<bool> CShowTrace(TEXT("s.ShowTrace"),
	false,TEXT("Enable Show Trace."),ECVF_Cheat);

USInteractComponent::USInteractComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

	TraceDistance=300.0f;
	CollisionChannel=ECC_WorldDynamic;
}



void USInteractComponent::BeginPlay()
{
	Super::BeginPlay();
	
	
}


bool USInteractComponent::IsBlocking() const
{
	return bIsBlocking;
}

void USInteractComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TraceInspection();
}

void USInteractComponent::TraceInspection()
{
	AActor* Actor=GetOwner();
	if(ASGameCharacter* Player=Cast<ASGameCharacter>(Actor))
	{
		FHitResult HitResult;

		const FVector Start =  Player->GetFollowCamera()->GetComponentLocation();
		
		const FVector End=Start+Player->GetFollowCamera()->GetForwardVector() * TraceDistance;
		
		GetWorld()->LineTraceSingleByChannel(HitResult,Start,End,CollisionChannel);

		// Console
		if(CShowTrace.GetValueOnAnyThread())
		{
			const FColor TraceColor=HitResult.bBlockingHit?FColor::Green:FColor::Red;
			DrawDebugLine(GetWorld(),Start,End,TraceColor,false,5.0f);
		}
		
		// close UI
		if(!HitResult.bBlockingHit)
		{
			bIsBlocking=false;
			if(FocusActor)
			{
				CloseInteractUI();
				OnUIClosed.Broadcast(Actor);
			}
			FocusActor=nullptr;
			return;
		}
		
		//open UI
		AActor* HitActor=HitResult.GetActor();

		if(HitActor)
		{
			bIsBlocking=true;
			if(HitActor == FocusActor)
			{
				return;
			}
			FocusActor=HitActor;
			OpenInteractUI();
			OnUIOpened.Broadcast(Actor);

		}

	}
}

void USInteractComponent::CloseInteractUI()
{
	if(WidgetDistance)
	{
		WidgetDistance->RemoveFromParent();
	}
}

void USInteractComponent::OpenInteractUI() 
{
	if(WidgetDistance == nullptr && ensure(DefaultWidgetClass))
	{
		WidgetDistance=CreateWidget<USWorldWidget_Interaction>(GetWorld(),DefaultWidgetClass);
		DISPLAY_LOG(TEXT("Create Widget!1"));
	}
	if(WidgetDistance)
	{
		WidgetDistance->AttachedActor=FocusActor;
		if(!WidgetDistance->IsInViewport())
		{
			WidgetDistance->AddToViewport();
			DISPLAY_LOG(TEXT("Create Widget!2"));
		}
	}
}

void USInteractComponent::TraceInteract(APawn* InstigatorActor)
{
	if(!FocusActor)
	{
		return;
	}
	if(ASInteractActor* actor=Cast<ASInteractActor>(FocusActor))
	{
		if(actor->Implements<USInteractInterface>())
		{
			actor->Interact_Implementation(InstigatorActor);
		}
		
	}
	
	DISPLAY_LOG(TEXT("Interact success!"));
}


