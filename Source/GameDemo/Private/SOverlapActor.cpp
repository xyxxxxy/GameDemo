
#include "SOverlapActor.h"
#include "Components/SphereComponent.h"
#include "SGameMacros.h"
#include "NiagaraComponent.h"

ASOverlapActor::ASOverlapActor()
{
 		PrimaryActorTick.bCanEverTick = true;
	
	SceneComp=CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent=SceneComp;
	
	SphereComp=CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	SphereComp->SetupAttachment(SceneComp);

	NiagaraComp=CreateDefaultSubobject<UNiagaraComponent>(TEXT("NiagaraComp"));
	NiagaraComp->SetupAttachment(SceneComp);

	//NiagaraComp->Activate(true);
	
	SphereComp->OnComponentBeginOverlap.AddDynamic(this,&ASOverlapActor::OnActorOverLap);

}

void ASOverlapActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASOverlapActor::OnActorOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(APawn* Pawn=Cast<APawn>(OtherActor))
	{
		DISPLAY_LOG(TEXT("Overlap!"));
		if(this->Implements<USInteractInterface>())
		{
			Execute_Interact(this,Pawn);
		}
	}
}

void ASOverlapActor::Interact_Implementation(APawn* InstigatorActor)
{
	ISInteractInterface::Interact_Implementation(InstigatorActor);
}



