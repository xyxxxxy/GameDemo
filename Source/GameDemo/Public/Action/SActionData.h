// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "SActionData.generated.h"

class USAction;
class UNiagaraSystem;

UENUM(BlueprintType)
namespace EActionCategory
{
	enum Type
	{
		NormalAction,
		MainAction
	};
}

USTRUCT(BlueprintType,Blueprintable)
struct GAMEDEMO_API FSActionProperty: public FTableRowBase
{
	GENERATED_BODY()

	FSActionProperty():
	Category(EActionCategory::NormalAction),
	ActionIcon(nullptr),
	ActionNiagara(nullptr)
	{
		ActionBrush.SetImageSize(FVector2D(256.0f,256.0f));
	}
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Action")
	FName ActionName;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Action")
	TEnumAsByte<EActionCategory::Type> Category;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Action")
	UTexture2D* ActionIcon;
	
	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Action")
	FSlateBrush ActionBrush;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Action")
	UNiagaraSystem* ActionNiagara;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Action")
	FName Description;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Action")
	TSubclassOf<USAction> ActionClass;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Action")
	FPostProcessSettings ProcessSettings;
	
};

