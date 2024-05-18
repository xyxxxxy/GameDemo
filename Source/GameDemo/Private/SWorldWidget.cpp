// Fill out your copyright notice in the Description page of Project Settings.


#include "SWorldWidget.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/SizeBox.h"
#include "Kismet/GameplayStatics.h"



void USWorldWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	SetUILocation();
}

void USWorldWidget::SetUILocation()
{
	if(!IsValid(AttachedActor))
	{
		RemoveFromParent();
		return;
	}
	FVector2D ScreenPosition;
	if(UGameplayStatics::ProjectWorldToScreen(GetOwningPlayer(),
		AttachedActor->GetActorLocation()+WorldOffset,
		ScreenPosition))
	{
		const float Scale=UWidgetLayoutLibrary::GetViewportScale(this);
		ScreenPosition/=Scale;
		if(ParentBox)
		{
			ParentBox->SetRenderTranslation(ScreenPosition);
		}
	};
}