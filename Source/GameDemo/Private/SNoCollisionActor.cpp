


#include "SNoCollisionActor.h"
#include "SGameMacros.h"
#include "Action/SActionComponent.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

ASNoCollisionActor::ASNoCollisionActor()
{
 
	PrimaryActorTick.bCanEverTick = true;

	SceneComp=CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent=SceneComp;

	StaticMeshComp=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComp->SetupAttachment(RootComponent);

	StaticMeshComp->SetCollisionProfileName("SetNoCollision");
	Tags={"NoCollision"};
	EffectTime=5.0f;
	TranslucentCollisionName="OverlapAll";
	bIsTranslucent=false;
}

void ASNoCollisionActor::ActionInteract_Implementation(AActor* InstigatorActor)
{
	ISActionInterface::ActionInteract_Implementation(InstigatorActor);

	EffectDelegate.BindUFunction(this,"Recover",InstigatorActor);

	SetNoCollisionMaterial();

	GetWorld()->GetTimerManager().SetTimer(EffectTimer,EffectDelegate,EffectTime,false);
	
	K2_CreateTimeWidget();
	
}

bool ASNoCollisionActor::IsTranslucent() const
{
	return bIsTranslucent;
}

void ASNoCollisionActor::Recover(AActor* InstigatorActor)
{
	if(USActionComponent* ActionComp=Cast<USActionComponent>
		(InstigatorActor->GetComponentByClass(USActionComponent::StaticClass())))
	{
		if(ActionComp->IsMainActionDeployed())
		{
			ActionComp->OnMainActionStartDeployed.Broadcast(ActionComp,InstigatorActor);
			DISPLAY_LOG(TEXT("recover to deploy material!"));
		}
		else
		{
			UpdateMaterial(nullptr);
			bIsTranslucent=false;
		}
	}
	if(StaticMeshComp)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(),RecoverSound,GetActorLocation());
		StaticMeshComp->SetCollisionProfileName("SetNoCollision");
		ClearTimer();
		OnEffectEnd.Broadcast();
		OnEffectEnd.Clear();
	}
}

void ASNoCollisionActor::SetNoCollisionMaterial()
{
	bIsTranslucent=true;
	UpdateMaterial(TranslucentMaterial);
	StaticMeshComp->SetCollisionProfileName(TranslucentCollisionName);
	
}

bool ASNoCollisionActor::UpdateMaterial(UMaterialInstance* NewMaterial)
{
	if(!StaticMeshComp)
	{
		return false;
	}
	int32 MaterialNum=StaticMeshComp->GetNumMaterials();
	for(int32 i=0;i<MaterialNum;++i)
	{
		StaticMeshComp->SetMaterial(i,NewMaterial);
	}
	return true;
}

void ASNoCollisionActor::ClearTimer()
{
	DISPLAY_LOG(TEXT("Clear TimerHandle!"));
	GetWorld()->GetTimerManager().ClearTimer(EffectTimer);
}













