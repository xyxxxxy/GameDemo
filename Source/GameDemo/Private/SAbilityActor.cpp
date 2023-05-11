

#include "SAbilityActor.h"

#include "NiagaraComponent.h"
#include "Action/SActionComponent.h"
#include "SGameMacros.h"
#include "UGameBlueprintFunctionLibrary.h"

void ASAbilityActor::Interact_Implementation(APawn* InstigatorActor)
{

	Super::Interact_Implementation(InstigatorActor);

	if(USActionComponent* ActionComp=Cast<USActionComponent>
		(InstigatorActor->GetComponentByClass(USActionComponent::StaticClass())))
	{
		DISPLAY_LOG(TEXT("Check Action Component!"));
		if(ActionComp->GetMainAction() && ActionComp->GetMainAction()->IsRunning())
		{
			ActionComp->GetMainAction()->StopAction_Implementation(InstigatorActor);
		}
		if(ensureMsgf(NewAction,TEXT("Where is your action??")))
		{
			ActionComp->AddAction(InstigatorActor,NewAction);
		}

	}

	K2_CreateActionWidget();
	Destroy();
}

void ASAbilityActor::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	bool bIsFound;
	FSActionProperty Property;
	UGameBlueprintFunctionLibrary::FindActionInDataTable(ActionName,bIsFound,Property);
	if(bIsFound)
	{
		NiagaraComp->SetAsset(Property.ActionNiagara);
	}
}

