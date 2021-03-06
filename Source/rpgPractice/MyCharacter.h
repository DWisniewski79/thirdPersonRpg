// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class RPGPRACTICE_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:
	void horizontalMovement(float value);
	void horizontalMouse(float value);
	void verticalMovement(float value);
	void verticalMouse(float value);
	
	void checkJump();

	UPROPERTY()
		bool jumping;

	UPROPERTY()
		UCameraComponent* camera;

	UPROPERTY()
		USpringArmComponent* arm;
	
	

	
	

};
