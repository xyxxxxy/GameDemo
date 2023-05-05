

#include "SAbilityActor.h"

#include "Action/SActionComponent.h"
#include "SGameMacros.h"

void ASAbilityActor::Interact_Implementation(APawn* InstigatorActor)
{

	Super::Interact_Implementation(InstigatorActor);

	if(USActionComponent* ActionComp=Cast<USActionComponent>
		(InstigatorActor->GetComponentByClass(USActionComponent::StaticClass())))
	{
		DISPLAY_LOG(TEXT("Check Action Component!"));
		if(ensureMsgf(NewAction,TEXT("Where is your action??")))
		{
			ActionComp->AddAction(InstigatorActor,NewAction);
		}

	}
	Destroy();
	
}
