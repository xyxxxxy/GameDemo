// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SGameCharacter.generated.h"

class USAttributeComponent;
class UPostProcessComponent;
class USActionComponent;
class USInteractComponent;
UCLASS()
class GAMEDEMO_API ASGameCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Camera",meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Camera",meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCameraComp;
	
public:
	
	ASGameCharacter();

protected:
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Control")
	float HorizontalSensitivity;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Control")
	float VerticalSensitivity;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="SkillComponent")
	USInteractComponent* InteractComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="SkillComponent")
	USAttributeComponent* AttributeComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="SkillComponent")
	USActionComponent* ActionComp;

	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="PostProcess")
	UPostProcessComponent* PostProcessComp;

	
	// Move
	void MoveForward(float value);

	void MoveRight(float value);

	void LookUp(float value);

	void Turn(float value);

	// Action
	void Interact();

	void StartSprint();

	void StopSprint();

	void JumpAction();
	
	void MainActionDeploy();
	
	void Action();

public:	
	
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;



	FORCEINLINE class UCameraComponent* GetFollowCamera() const
	{
		return FollowCameraComp;
	}
};





