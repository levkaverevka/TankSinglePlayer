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

DECLARE_LOG_CATEGORY_EXTERN(TankInfo, Warning, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTankFired, int32, AmmoCount);

UCLASS()
class FOXTOWERPROJ_API ATankPawn : public ATurretPawn
{
	GENERATED_BODY()
	
public:

	ATankPawn();

	UPROPERTY(BlueprintAssignable, Category = "Ammo")
	FOnTankFired OnTankFired;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime);
protected:

	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);
	void OnMoveReleased(const FInputActionValue& Value);
	void MoveActor();
	void Turn(const FInputActionValue& Value);
	void TankFire(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void LookAtCursor();

	UFUNCTION()
	void RotateBarrelFunction(const FRotator& LookAtRotation, float DeltaTime, float InterpSpeed);

	UFUNCTION()
	void TankReload();

	UFUNCTION()
	bool IsOnGround();

	float MoveValue = 0.f;
	FVector ForwardMove = FVector::ZeroVector;
	float CurrentSpeed = 0.f;
	float TargetSpeed = 0.f;
	FRotator InterpolatedRotation;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BarrelMesh;

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
	UInputAction* LookAction;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammo")
	int AmmoCount = 10;

	bool bIsReloading = false;

	UPROPERTY()
	float ReloadTime = 2.f;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "SFX")
	UAudioComponent* MoveSfxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SFX")
	USoundBase* MoveSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SFX")
	USoundBase* ReloadSound;

	UPROPERTY()
	FTimerHandle ReloadTimer;

};
