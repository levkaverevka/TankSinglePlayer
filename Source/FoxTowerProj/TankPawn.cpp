// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"


ATankPawn::ATankPawn()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(CapsuleComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(TankIMC, 0);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("tank is missing UEnhancedInputLocalPlayerSubsystem !"));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("tank has no controller!"));
	}
}

void ATankPawn::Move(const FInputActionValue& Value)
{
	float MoveValue = Value.Get<float>();
	UE_LOG(LogTemp, Warning, TEXT("MoveValue %f"), MoveValue);
}

void ATankPawn::Turn(const FInputActionValue& Value)
{
	float TurnValue = Value.Get<float>();
	UE_LOG(LogTemp, Warning, TEXT("TurnValue %f"), TurnValue);
}

void ATankPawn::Fire(const FInputActionValue& Value)
{
	float bPressed = Value.Get<bool>();
	UE_LOG(LogTemp, Warning, TEXT("Fire: %s"), *FString(bPressed ? TEXT("TRUE") : TEXT("FALSE")));
}

void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super:: SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATankPawn::Move);
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ATankPawn::Turn);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &ATankPawn::Fire);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("EnhancedInputComponent is missing"))
	}
}


