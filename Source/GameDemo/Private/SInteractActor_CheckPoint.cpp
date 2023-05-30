// Fill out your copyright notice in the Description page of Project Settings.

#include "SInteractActor_CheckPoint.h"
#include "Blueprint/UserWidget.h"
#include "SGameMacros.h"


ASInteractActor_CheckPoint::ASInteractActor_CheckPoint()
{
	PlayerLocationComp = CreateDefaultSubobject<USceneComponent>(TEXT("PlayerLocationComp"));

	PlayerLocationComp->SetupAttachment(InteractComp);
	
}

void ASInteractActor_CheckPoint::Interact_Implementation(APawn* InstigatorActor)
{
	Super::Interact_Implementation(InstigatorActor);

	DISPLAY_LOG(FString("Number : ").Append(FString::FromInt(CPNumber)));
	
	if(CheckWidgetInstance && CheckWidgetInstance->IsInViewport())
	{
		return;
	}
	
	LastCheckPoint = this;

	if(ensure(CheckWidgetClass))
	{
		CheckWidgetInstance = CreateWidget<UUserWidget>(GetWorld(),CheckWidgetClass);
		if(CheckWidgetInstance)
		{
			CheckWidgetInstance->AddToViewport();
		}
	}
}

void ASInteractActor_CheckPoint::Respawn(APawn* Pawn,APlayerController* PC)
{
	if(LastCheckPoint != nullptr)
	{
		PC->UnPossess();
		Pawn->SetActorTransform(FTransform(LastCheckPoint->PlayerLocationComp->GetComponentRotation(),
	LastCheckPoint->PlayerLocationComp->GetComponentLocation()));
		PC->Possess(Pawn);
	}
}

void ASInteractActor_CheckPoint::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	CPNumber++;
}
