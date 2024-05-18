// Fill out your copyright notice in the Description page of Project Settings.


#include "SInteractActor.h"
#include "SGameMacros.h"
#include "UGameBlueprintFunctionLibrary.h"


ASInteractActor::ASInteractActor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComp=CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent=SceneComp;

	InteractComp=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InteractComp"));
	InteractComp->SetupAttachment(RootComponent);
	
	InteractComp->SetCollisionProfileName("Item");

	InteractComp->SetRenderCustomDepth(false);
	InteractComp->SetCustomDepthStencilValue(10);
	
}

void ASInteractActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	SetMesh();
}

void ASInteractActor::GetCategory_Implementation(FName& Name)
{

	ActorGetCategory(Name);
	
}

void ASInteractActor::BeginPlay()
{
	Super::BeginPlay();
}

void ASInteractActor::SetMesh()
{
	bool bIsFound;
	FSItemProperty ItemCategory;
	UGameBlueprintFunctionLibrary::FindItemInDataTable(Item,bIsFound,ItemCategory);
	if(bIsFound)
	{
		InteractComp->SetStaticMesh(ItemCategory.InteractStaticMesh);
	}
	else
	{
		DISPLAY_LOG(TEXT("Fail to Set StaticMesh!"));
	}
}

void ASInteractActor::ActorGetCategory(FName& CategoryName)
{
	bool bIsFound;
	FSItemProperty ItemProperty;
	UGameBlueprintFunctionLibrary::FindItemInDataTable(Item,bIsFound,ItemProperty);

	if(!bIsFound)
	{
		return;
	}

	switch (ItemProperty.Category)
	{
	case ECategory::Pick_Up:
		CategoryName = FName("Pick Up");
		break;
	case ECategory::Interact:
		CategoryName = FName("Interact");
		break;
	case ECategory::Dialogue:
		CategoryName = FName("Dialogue");
		break;
	default:
		CategoryName = FName("None");
		break;
	}
}

void ASInteractActor::CloseCustomDepth_Implementation()
{
	ISInteractInterface::CloseCustomDepth_Implementation();

	InteractComp->SetRenderCustomDepth(false);
}

void ASInteractActor::OpenCustomDepth_Implementation()
{
	ISInteractInterface::OpenCustomDepth_Implementation();

	InteractComp->SetRenderCustomDepth(true);
}


