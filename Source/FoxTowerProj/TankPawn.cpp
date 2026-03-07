// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "MyPlayerController.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "Components/AudioComponent.h"
#include <Kismet/KismetSystemLibrary.h>
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY(TankInfo);

ATankPawn::ATankPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->bUsePawnControlRotation = true;

	BarrelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Barrel"));
	BarrelMesh->SetupAttachment(TurretMesh);

	ProjectileSpawnComponent->SetupAttachment(BarrelMesh);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;

	DustFX = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Dust Spawn Component"));
	DustFX->SetupAttachment(CapsuleComponent);
	DustFX->SetAutoActivate(false);
	bUseControllerRotationYaw = false;

	MoveSfxComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Movement sound"));
	MoveSfxComponent->SetupAttachment(ProjectileSpawnComponent);
	MoveSfxComponent->SetAutoActivate(false);
}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();
	AMyPlayerController* PlayerController = Cast<AMyPlayerController>(GetController());
	if (PlayerController)
	{
		//EnhancedInput
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(TankIMC, 0);
		}
		else
		{
			UE_LOG(TankInfo, Warning, TEXT("tank is missing UEnhancedInputLocalPlayerSubsystem !"));
		}
		//mouse coursor
		PlayerController->bShowMouseCursor = true;
		PlayerController->bEnableClickEvents = true;
		PlayerController->bEnableMouseOverEvents = true;
	}
	else
	{
		UE_LOG(TankInfo, Warning, TEXT("tank has no controller!"));
	}
}

void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const FVector Forward = GetActorForwardVector();
	const FVector Location = GetActorLocation();

	MoveActor();

	DrawDebugLine(GetWorld(), Location, Location + Forward * 2200, FColor::Emerald, false, -1.f, 0, 2.f);
	DrawDebugCoordinateSystem(GetWorld(), GetActorLocation(), GetActorRotation(), 200.f, false, 0.f, 0, 2.f);
	/*LookAtCursor();*/
}

void ATankPawn::Move(const FInputActionValue& Value)
{
	MoveValue = Value.Get<float>();
}

void ATankPawn::OnMoveReleased(const FInputActionValue& Value)
{
	MoveValue = 0.0f;
}

void ATankPawn::MoveActor()
{
	if (IsOnGround())
	{
		float DeltaTime = GetWorld()->GetDeltaSeconds();
		TargetSpeed = MoveValue * MoveSpeed;
		float InterpSpeed = (FMath::Abs(CurrentSpeed) < FMath::Abs(TargetSpeed)) ? AccelerationSpeed : DecelerationSpeed;
		CurrentSpeed = FMath::FInterpTo(CurrentSpeed, TargetSpeed, DeltaTime, InterpSpeed);
		ForwardMove = FVector(CurrentSpeed * DeltaTime, 0.f, 0.f);
		AddActorLocalOffset(ForwardMove, false);
		if (CurrentSpeed != 0)
		{
			if (!DustFX->IsActive())
			{
				DustFX->Activate();

			}
		}
		else
		{
			DustFX->Deactivate();
			MoveSfxComponent->Stop();
		}
	}
	if (!MoveSfxComponent->IsPlaying() && CurrentSpeed > 0)
	{
		MoveSfxComponent->Play();
	}
}

void ATankPawn::Turn(const FInputActionValue& Value)
{
	float TurnValue = Value.Get<float>();
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	FRotator Rotation = FRotator(0.f, TurnValue * RotationSpeed * DeltaTime, 0.f);
	AddActorLocalRotation(Rotation,false);
}

void ATankPawn::TankFire(const FInputActionValue& Value)
{
	UE_LOG(TankInfo, Log, TEXT("=== TANKFIRE WORKS ==="));
	if (AmmoCount > 0)
	{
		ATurretPawn::Fire();
		UE_LOG(TankInfo, Log, TEXT("Ammo count is: %d"), AmmoCount);
		AmmoCount --;
		OnTankFired.Broadcast(AmmoCount);
		if (AmmoCount == 0)
		{
			TankReload();
		}
	}
	
}

void ATankPawn::Look(const FInputActionValue& Value)
{
	UE_LOG(LogTemp, Warning, TEXT("LOOK WORKS"));
	FVector2D LookAxis = Value.Get<FVector2D>();

	AddControllerYawInput(LookAxis.X);
	AddControllerPitchInput(LookAxis.Y);
}

void ATankPawn::LookAtCursor()
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	if (PlayerController)
	{
		FHitResult HitResult;
		float DeltaTime = GetWorld()->GetDeltaSeconds();
		PlayerController->GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
		FVector HitLocation = HitResult.ImpactPoint;
		if (HitLocation != FVector(0.f, 0.f, 0.f))
		{
			FVector TurretLocalDirection = TurretMesh->GetComponentTransform().InverseTransformPosition(HitLocation);
			FRotator LookAtTurretRotation = TurretLocalDirection.Rotation();
			FVector BarrelLocalDirection = TurretMesh->GetComponentTransform().InverseTransformPosition(HitLocation);
			FRotator LookAtBarrelRotation = BarrelLocalDirection.Rotation();
			RotateTurretFunction(LookAtTurretRotation, DeltaTime, 5.f);
			RotateBarrelFunction(LookAtBarrelRotation, DeltaTime, 5.f);
			DrawDebugSphere(GetWorld(), HitLocation, 20.f, 12, FColor::Red, false, -1.f, 0, 2.f);
		}
	}
	
}

void ATankPawn::RotateBarrelFunction(const FRotator& LookAtRotation, float DeltaTime, float InterpSpeed)
{
	FRotator BarrelRotation = FRotator(LookAtRotation.Pitch, -180.f, 0.f);
	FRotator InterpolatedBarrelRotation = FMath::RInterpTo(BarrelMesh->GetRelativeRotation(), BarrelRotation, DeltaTime, InterpSpeed);
	BarrelMesh->SetRelativeRotation(InterpolatedBarrelRotation);
}

void ATankPawn::TankReload()
{
	if (!bIsReloading)
	{
		bIsReloading = true;
		UGameplayStatics::PlaySound2D(this, ReloadSound);
		GetWorldTimerManager().SetTimer(ReloadTimer, [this]() {AmmoCount += 20; bIsReloading = false; }, ReloadTime, false);
	}
}

bool ATankPawn::IsOnGround()
{
	FHitResult Hit;
	FVector StartLocation = GetActorLocation();
	FVector EndLocation = StartLocation - FVector(0.f, 0.f, 5.f);
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Green, false, 0.f, 0, 2.f);
	return GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_Visibility);
}

void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super:: SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATankPawn::Look);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATankPawn::Move);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &ATankPawn::OnMoveReleased);
		EnhancedInputComponent->BindAction(TurnAction, ETriggerEvent::Triggered, this, &ATankPawn::Turn);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &ATankPawn::TankFire);
	}
	else
	{
		UE_LOG(TankInfo, Warning, TEXT("EnhancedInputComponent is missing"))
	}
}


