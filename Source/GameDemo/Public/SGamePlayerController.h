
#pragma once

#include "CoreMinimal.h"
#include "SUIManagerInterface.h"
#include "GameFramework/PlayerController.h"
#include "SGamePlayerController.generated.h"

class UUserWidget;

UCLASS()
class GAMEDEMO_API ASGamePlayerController : public APlayerController,public ISUIManagerInterface
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="UI")
	TSubclassOf<UUserWidget> DefaultMainWidgetClass;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="UI")
	TSoftClassPtr<UUserWidget> PauseMenuClass;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="UI")
	TSubclassOf<UUserWidget> ActionMenuClass;

	UPROPERTY(EditDefaultsOnly,Category="UI")
	float DelayTime = 1.0f;

	FTimerHandle WidgetTimer;

	FTimerDelegate WidgetDelegate;
	
	virtual void OnPossess(APawn* InPawn) override;

	void TogglePauseMenu();


	UFUNCTION(BlueprintCallable,Category="UI")
	void OpenActionMenu();
	
	void CloseActionMenu();

	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;

	
public:
	
	UFUNCTION(BlueprintCallable,Category="UI")
	void CreateMainWidget();

private:

	UPROPERTY()
	UUserWidget* MainWidgetInstance;

	UPROPERTY()
	UUserWidget* PauseMenuInstance;
	
	UPROPERTY()
	UUserWidget* ActionMenuInstance;
};
