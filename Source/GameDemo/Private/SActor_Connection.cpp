// Fill out your copyright notice in the Description page of Project Settings.


#include "SActor_Connection.h"

#include "Kismet/KismetMathLibrary.h"

// Sets default values
ASActor_Connection::ASActor_Connection()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComp=CreateDefaultSubobject<USceneComponent>(TEXT("RootComp"));
	RootComponent=RootComp;

	SceneComp=CreateDefaultSubobject<USceneComponent>(TEXT("SceneComp"));
	SceneComp->SetupAttachment(RootComponent);
	
	ConnectionComp=CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ConnectionComp"));
	ConnectionComp->SetupAttachment(SceneComp);

	ConnectionComp->OnComponentHit.AddDynamic(this,&ASActor_Connection::StopGrow);

	Time=0.0f;
}


void ASActor_Connection::Connect()
{
	
	float TotalLength=UKismetMathLibrary::VSize(EndLocation-StartLocation);
	float EndScale=TotalLength/UKismetMathLibrary::VSize(RelativeLocation);
	float Scale = FMath::Lerp(0.1f,EndScale,Time/2);
	SetActorScale3D(FVector(Scale,1.0f,1.0f));
}

void ASActor_Connection::BeginPlay()
{
	Super::BeginPlay();
	RelativeLocation = ConnectionComp->GetRelativeLocation()*2.0f;
	
	FTimerHandle DestroyTimerHandle;
	GetWorld()->GetTimerManager().SetTimer(DestroyTimerHandle,[this]()
	{
		Destroy();
	},ExistTime,false);
	
}

void ASActor_Connection::StopGrow(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	if(APawn* Pawn = Cast<APawn>(OtherActor))
	{
		EndLocation /= 2.0f;
	}
	
	if(!HitComponent->IsSimulatingPhysics())
	{
		SetActorTickEnabled(false);
	}

}

void ASActor_Connection::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(Time>=2.0f)
	{
		return;
	}
	Time+=DeltaTime;
	Connect();

}

