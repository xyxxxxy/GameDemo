


#include "SNoCollisionActor.h"

#include "SNoCollisionComponent.h"

ASNoCollisionActor::ASNoCollisionActor()
{
 
	PrimaryActorTick.bCanEverTick = true;

	SceneComp=CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	RootComponent=SceneComp;

	StaticMeshComp=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComp->SetupAttachment(RootComponent);

	CollisionComp = CreateDefaultSubobject<USNoCollisionComponent>(TEXT("CollisionComp"));
}















