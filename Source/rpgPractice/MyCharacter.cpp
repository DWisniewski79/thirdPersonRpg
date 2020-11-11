// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include "Components/InputComponent.h"
// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CAMERA"));
	//camera->AttachTo(RootComponent);

	//Creating a third person perspective using a Spring Arm Component
	//READ UP ON DEFAULT SUB OBJECTS
	arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	arm->AttachTo(RootComponent);
	arm->TargetArmLength = 300.f;
	arm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));

	//Enabling camera lag allows for smoother camera movement
	arm->bEnableCameraLag = true;
	arm->CameraLagSpeed = 2;
	arm->CameraLagMaxDistance = 1.5f;

	arm->bEnableCameraRotationLag = true;
	arm->CameraRotationLagSpeed = 4;
	arm->CameraLagMaxTimeStep = 1;

	camera->AttachTo(arm, USpringArmComponent::SocketName);

	jumping = false;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (jumping)
	{
		Jump();
	}

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	InputComponent->BindAxis("Horizontal", this, &AMyCharacter::horizontalMovement);
	InputComponent->BindAxis("Vertical", this, &AMyCharacter::verticalMovement);
	InputComponent->BindAxis("HorizontalMouse", this, &AMyCharacter::horizontalMouse);
	InputComponent->BindAxis("VerticalMouse", this, &AMyCharacter::verticalMouse);

	InputComponent->BindAction("Jump", IE_Pressed, this, &AMyCharacter::checkJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AMyCharacter::checkJump);
}

void AMyCharacter::horizontalMovement(float value)
{
	if (value)
	{
		AddMovementInput(GetActorRightVector(),value);
	}
}

void AMyCharacter::horizontalMouse(float value)
{
	if (value)
	{
		AddActorLocalRotation(FRotator(0, value, 0));
	}
}

void AMyCharacter::verticalMovement(float value)
{
	if (value)
	{
		AddMovementInput(GetActorForwardVector(), value);
	}
}

void AMyCharacter::verticalMouse(float value)
{
	if (value)
	{
		float temp = arm->GetRelativeRotation().Pitch + value;

		if (temp < 25 && temp > -65)
		{
			arm->AddLocalRotation(FRotator(value, 0, 0));
		}
	}
}


void AMyCharacter::checkJump()
{
	if (jumping)
	{
		jumping = false;
	}
	else
	{
		jumping = true;
	}
}

/*void AMyCharacter::jump(float value)
{
	if (value)
	{
		InputMovement
	}
}*/



