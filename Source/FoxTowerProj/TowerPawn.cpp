// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerPawn.h"
#include "Perception/PawnSensingComponent.h"

ATowerPawn::ATowerPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	PawnSensor = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Awareness"));
};

void ATowerPawn::BeginPlay()
{
	Super::BeginPlay();

	if (PawnSensor)
	{
		PawnSensor->OnSeePawn.AddDynamic(this, &ATowerPawn::OnSeePawn);
	}
}

void ATowerPawn::OnSeePawn(APawn* OtherPawn)
{
	CurrentTarget = OtherPawn;
	UE_LOG(LogTemp, Warning, TEXT("SEE someone!!"));
	GetWorldTimerManager().SetTimer(FTimer, this, &ATowerPawn::Fire, FireInterval, true);
	//UE_LOG(LogTemp, Warning, TEXT("I SEE SOMEONE! %s"), *OtherPawn->GetName());
}

void ATowerPawn::Fire()
{
	UE_LOG(LogTemp, Warning, TEXT("BAM!"));
}

void ATowerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentTarget)
	{
		float RotationSpeed = 300.f;
		FVector Direction = CurrentTarget->GetActorLocation() - GetActorLocation();
		FRotator LookAtRotation = Direction.Rotation() /*- GetActorRotation()*/;
		FRotator TowerTurretRotation = FRotator(0.f, LookAtRotation.Yaw, 0.f);
		FRotator InterpolatedRotation = FMath::RInterpTo(TurretMesh->GetComponentRotation(),TowerTurretRotation,DeltaTime,100.f);
		TurretMesh->SetRelativeRotation(InterpolatedRotation);
	}
}

void ATowerPawn::LookAtPawn(APawn* OtherPawn)
{
	CurrentTarget = OtherPawn;
}