// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurretPawn.h"
#include "InputActionValue.h"
#include "TankPawn.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UInputComponent;
class UNiagaraComponent;
class UAudioComponent;
/**
 * 
 */
UCLASS()
class FOXTOWERPROJ_API ATankPawn : public ATurretPawn
{
	GENERATED_BODY()
	
public:

	ATankPawn();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime);
protected:

	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);
	void OnMoveReleased(const FInputActionValue& Value);
	void MoveActor();
	void Turn(const FInputActionValue& Value);
	void TankFire(const FInputActionValue& Value);
	void LookAtCursor();


	float MoveValue = 0.f;
	FVector ForwardMove = FVector::ZeroVector;
	float CurrentSpeed = 0.f;
	float TargetSpeed = 0.f;
	FRotator InterpolatedRotation;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCameraComponent> Camera;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VFX")
	UNiagaraComponent* DustFX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputMappingContext* TankIMC;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* TurnAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	UInputAction* FireAction;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float AccelerationSpeed = 5.f; 

	UPROPERTY(EditAnywhere, Category = "Movement")
	float DecelerationSpeed = 6.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Speed")
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Speed")
	float RotationSpeed;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "SFX")
	UAudioComponent* MoveSfxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SFX")
	USoundBase* MoveSound;

};
