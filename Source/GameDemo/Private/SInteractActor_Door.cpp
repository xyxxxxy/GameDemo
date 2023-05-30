// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractActor_Door.h"

#include "Components/TimelineComponent.h"

void ASInteractActor_Door::BeginPlay()
{
	Super::BeginPlay();

	UpdateFunctionFloat.BindDynamic(this,&ASInteractActor_Door::UpdateTimelineComp);
	if(ensureMsgf(DoorTimelineFloatCurve,TEXT("your curve?")))
	{
		DoorTimelineComp->AddInterpFloat(DoorTimelineFloatCurve,UpdateFunctionFloat);
	}
}

ASInteractActor_Door::ASInteractActor_Door()
{
	DoorFrameComp=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorFrameComp"));
	DoorFrameComp->SetupAttachment(RootComponent);

	DoorTimelineComp=CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimelineComp"));

	InteractComp->AttachToComponent(DoorFrameComp,FAttachmentTransformRules::KeepRelativeTransform);
}

void ASInteractActor_Door::Interact_Implementation(APawn* InstigatorActor)
{
	Super::Interact_Implementation(InstigatorActor);

	if(bIsOpen)
	{
		DoorTimelineComp->Reverse();
		bIsOpen = false;
	}
	else
	{
		DoorTimelineComp->Play();
		bIsOpen = true;
	}
	
}

void ASInteractActor_Door::UpdateTimelineComp(float Output)
{
	const FRotator DoorNewRotation=FRotator(0.0f,Output,0.0f);
	InteractComp->SetRelativeRotation(DoorNewRotation);
	
}
