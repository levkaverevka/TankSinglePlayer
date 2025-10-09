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
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(TurretMesh);

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

void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector Forward = GetActorForwardVector();
	const FVector Location = GetActorLocation();

	DrawDebugLine(GetWorld(), Location, Location + Forward * 2200, FColor::Emerald, false, -1.f, 0, 2.f);
	DrawDebugCoordinateSystem(GetWorld(), GetActorLocation(), GetActorRotation(), 200.f, false, 0.f, 0, 2.f);
}

void ATankPawn::Move(const FInputActionValue& Value)
{
	float MoveValue = Value.Get<float>();
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	float CurrentMove = 0.f;
	float InterpValue = FMath::FInterpTo(CurrentMove, MoveSpeed * MoveValue, 5.f, 1.f);
	const FVector ForwardMove = FVector(InterpValue * DeltaTime, 0.f, 0.f);
	AddActorLocalOffset(ForwardMove, false);
	UE_LOG(LogTemp, Warning, TEXT("MoveValue %f"), MoveValue);
}

void ATankPawn::Turn(const FInputActionValue& Value)
{
	float TurnValue = Value.Get<float>();
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	FRotator Rotation = FRotator(0.f, TurnValue * RotationSpeed * DeltaTime, 0.f);
	AddActorLocalRotation(Rotation,false);
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


