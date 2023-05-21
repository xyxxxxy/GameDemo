// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Sitem.generated.h"

UENUM(BlueprintType)
namespace ECategory
{
	enum Type
	{
		Pick_Up,
		Interact,
		Dialogue
	};

}

USTRUCT(BlueprintType)
struct FSItem
{
	GENERATED_BODY()
	
	FSItem()
	:ID("None")
	,Number(0)
	{}
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	FName ID;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	int Number;

};
USTRUCT(BlueprintType,blueprintable)
struct GAMEDEMO_API FSItemProperty : public FTableRowBase
{
	GENERATED_BODY()

	FSItemProperty()
	:ID("None")
	,Category(ECategory::Interact)
	,Icon()
	,InteractStaticMesh(nullptr)
	{}
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	FName ID;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	TEnumAsByte<ECategory::Type> Category;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	UTexture2D* Icon;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	UStaticMesh* InteractStaticMesh;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Item")
	FText Description;
};
