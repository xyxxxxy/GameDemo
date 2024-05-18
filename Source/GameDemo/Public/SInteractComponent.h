// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SInteractComponent.generated.h"


class USWorldWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnInteractChanged,
                                            AActor*, Instigator);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAMEDEMO_API USInteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	USInteractComponent();

protected:

	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere,Category="Interact")
	float TraceDistance;
	
	UPROPERTY(EditDefaultsOnly,Category="Interact")
	TEnumAsByte<ECollisionChannel> CollisionChannel;

	UPROPERTY(EditDefaultsOnly,Category="UI")
	TSubclassOf<USWorldWidget> DefaultWidgetClass;

	UPROPERTY()
	USWorldWidget* WidgetDistance;

	UPROPERTY()
	bool bIsBlocking = false;

	UFUNCTION(BlueprintCallable,Category="Interact")
	void TraceInspection();

	void CloseInteractUI();

	void OpenInteractUI();

	UPROPERTY()
	AActor* FocusActor;
	
private:
	bool SetTickEnabled(bool NewState);
	
public:

	UPROPERTY(BlueprintAssignable)
	FOnInteractChanged OnUIClosed;

	UPROPERTY(BlueprintAssignable)
	FOnInteractChanged OnUIOpened;

	bool IsBlocking() const;

	void TraceInteract(APawn* InstigatorActor);

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
};
