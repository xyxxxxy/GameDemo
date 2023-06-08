

#include "SGameCharacter.h"

#include "SAttributeComponent.h"
#include "SInteractComponent.h"
#include "Action/SActionComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/PostProcessComponent.h"

ASGameCharacter::ASGameCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	HorizontalSensitivity = 1.0f;
	VerticalSensitivity = 1.0f;
	bUseControllerRotationPitch=false;
	bUseControllerRotationRoll=false;
	bUseControllerRotationYaw=false;

	GetCharacterMovement()->bOrientRotationToMovement=true;
	GetCharacterMovement()->RotationRate=FRotator(0.0f,540.0f,0.0f);
	GetCharacterMovement()->JumpZVelocity=600.0f;
	GetCharacterMovement()->AirControl=0.2f;

	SpringArmComp=CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength=300.0f;
	SpringArmComp->bUsePawnControlRotation=true;

	FollowCameraComp=CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCameraComp"));
	FollowCameraComp->SetupAttachment(SpringArmComp,USpringArmComponent::SocketName);
	FollowCameraComp->bUsePawnControlRotation=false;

	InteractComp=CreateDefaultSubobject<USInteractComponent>(TEXT("InteractComp"));

	ActionComp=CreateDefaultSubobject<USActionComponent>(TEXT("ActionComp"));

	AttributeComp = CreateDefaultSubobject<USAttributeComponent>(TEXT("AttributeComp"));

	PostProcessComp=CreateDefaultSubobject<UPostProcessComponent>(TEXT("PostProcessComp"));
	PostProcessComp->SetupAttachment(RootComponent);

	PostProcessComp->bEnabled=false;
	
}


void ASGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward",this,&ASGameCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight",this,&ASGameCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp",this,&ASGameCharacter::LookUp);
	PlayerInputComponent->BindAxis("Turn",this,&ASGameCharacter::Turn);
	
	PlayerInputComponent->BindAction("Interact",IE_Pressed,this,&ASGameCharacter::Interact);
	PlayerInputComponent->BindAction("Sprint",IE_Pressed,this,&ASGameCharacter::StartSprint);
	PlayerInputComponent->BindAction("Sprint",IE_Released,this,&ASGameCharacter::StopSprint);

	PlayerInputComponent->BindAction("Jump",IE_Pressed,this,&ASGameCharacter::JumpAction);

	PlayerInputComponent->BindAction("MainActionDeploy",IE_Pressed,this,&ASGameCharacter::MainActionDeploy);
	PlayerInputComponent->BindAction("Action",IE_Pressed,this,&ASGameCharacter::Action);
}

void ASGameCharacter::MoveForward(float value)
{
	if(Controller!=nullptr && value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.0f,Rotation.Yaw,0.0f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction,value);
	}
}

void ASGameCharacter::MoveRight(float value)
{
	if(Controller != nullptr && value != 0.0f)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation( 0.0f,Rotation.Yaw,0.0f);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction,value);
	}
}

void ASGameCharacter::LookUp(float value)
{
	AddControllerPitchInput(value * VerticalSensitivity);
}

void ASGameCharacter::Turn(float value)
{
	AddControllerYawInput(value * HorizontalSensitivity);
}

void ASGameCharacter::Interact()
{
	if(InteractComp->IsBlocking())
	{
		InteractComp->TraceInteract(this);
	}
}

void ASGameCharacter::StartSprint()
{
	if(ActionComp)
	{
		ActionComp->StartActionByName(this,"Sprint");
	}
}

void ASGameCharacter::StopSprint()
{
	if(ActionComp)
	{
		ActionComp->StopActionByName(this,"Sprint");
	}
}

void ASGameCharacter::JumpAction()
{
	if(ActionComp)
	{
		ActionComp->StartActionByName(this,"Jump");
	}
}

void ASGameCharacter::MainActionDeploy()
{
	if(ActionComp && ActionComp->HaveMainAction())
	{
		if(ActionComp->IsMainActionDeployed())
		{
			ActionComp->StopActionByName(this,FName("MainAction"));
		}
		else
		{
			if(ActionComp->ShouldStartDeploy(this))
			{
				ActionComp->SetMainActionDeployed(true);
			}
		}

	}
}

void ASGameCharacter::Action()
{
	if(ActionComp && ActionComp->HaveMainAction() && ActionComp->IsMainActionDeployed())
	{
		ActionComp->StartActionByName(this,"MainAction");
	}
}


