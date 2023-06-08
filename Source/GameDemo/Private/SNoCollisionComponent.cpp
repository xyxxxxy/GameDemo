


#include "SNoCollisionComponent.h"
#include "SGameMacros.h"
#include "Action/SActionComponent.h"
#include "Action/SMainAction_NoCollision.h"
#include "Kismet/GameplayStatics.h"


bool USNoCollisionComponent::IsTranslucent() const
{
	return bIsTranslucent;
}

void USNoCollisionComponent::ActionInteract_Implementation(AActor* InstigatorActor)
{
	ISActionInterface::ActionInteract_Implementation(InstigatorActor);

	 EffectDelegate.BindUFunction(this,"Recover",InstigatorActor);
	
	 SetNoCollisionMaterial();
	
	GetWorld()->GetTimerManager().SetTimer(EffectTimer,EffectDelegate,EffectTime,false);
	
	OnEffectStart.Broadcast();
	
	K2_CreateTimeWidget();
}

void USNoCollisionComponent::Recover(AActor* InstigatorActor)
{
	if(USActionComponent* ActionComp=Cast<USActionComponent>
		(InstigatorActor->GetComponentByClass(USActionComponent::StaticClass())))
	{
		if(ActionComp->IsMainActionDeployed() &&
			ActionComp->GetMainAction()->IsA<USMainAction_NoCollision>())
		{
			ActionComp->OnMainActionStartDeployed.Broadcast(ActionComp,InstigatorActor);
			//DISPLAY_LOG(TEXT("recover to deploy material!"));
		}
		else
		{

			UpdateMaterial(nullptr);
			bIsTranslucent=false;
		}
	}
	if(CollisionComp)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(),RecoverSound,CollisionComp->GetComponentLocation());
		CollisionComp->SetCollisionProfileName("SetNoCollision");
		if(bShouldSimulatePhysics)
		{
			CollisionComp->SetSimulatePhysics(true);		
		}
		ClearTimer();
		OnEffectEnd.Broadcast();
		OnEffectEnd.Clear();
	}
}

void USNoCollisionComponent::SetNoCollisionMaterial()
{
	bIsTranslucent=true;
	UpdateMaterial(TranslucentMaterial);
	
	if(bShouldSimulatePhysics)
	{
		CollisionComp->SetSimulatePhysics(false);
	}
	
	CollisionComp->SetCollisionProfileName(TranslucentCollisionName);
}

bool USNoCollisionComponent::UpdateMaterial(UMaterialInstance* NewMaterial)
{
	if(!CollisionComp)
	{
		return false;
	}
	int32 MaterialNum = CollisionComp->GetNumMaterials();
	for(int32 i=0;i<MaterialNum;++i)
	{
		CollisionComp->SetMaterial(i,NewMaterial);
	}
	return true;
}

void USNoCollisionComponent::ClearTimer()
{
	//DISPLAY_LOG(TEXT("Clear TimerHandle!"));
	GetWorld()->GetTimerManager().ClearTimer(EffectTimer);
}

void USNoCollisionComponent::BeginPlay()
{
	Super::BeginPlay();
	//DISPLAY_LOG(TEXT("Comp Begin"));
	ParentActor = GetOwner();
	
	if(ParentActor)
	{
		CollisionComp = Cast<UStaticMeshComponent>
		(ParentActor->GetComponentByClass(UStaticMeshComponent::StaticClass()));
		if(ensure(CollisionComp))
		{
			CollisionComp->SetCollisionProfileName("SetNoCollision");
			ParentActor->Tags = {"NoCollision"};
			EffectTime=5.0f;
			TranslucentCollisionName="OverlapAll";
			bIsTranslucent=false;
			CollisionComp->SetSimulatePhysics(bShouldSimulatePhysics);
		}
	}
	
}










