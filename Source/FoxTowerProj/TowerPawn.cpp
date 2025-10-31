// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerPawn.h"
#include "Perception/PawnSensingComponent.h"

ATowerPawn::ATowerPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	PawnSensor = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Awareness"));
	TurretMesh->SetUsingAbsoluteRotation(true);
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
	GetWorldTimerManager().ClearTimer(NullPawnTimer);
	GetWorldTimerManager().SetTimer(NullPawnTimer, this, &ATowerPawn::NullPawn, 1.f, false);

	GetWorldTimerManager().SetTimer(FireTimer, this, &ATowerPawn::Fire, FireInterval, true);
	//UE_LOG(LogTemp, Warning, TEXT("I SEE SOMEONE! %s"), *OtherPawn->GetName());
}

void ATowerPawn::NullPawn()
{
	CurrentTarget = nullptr;
	GetWorldTimerManager().ClearTimer(FireTimer);
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
		FVector Direction = CurrentTarget->GetActorLocation() - TurretMesh->GetComponentLocation();
		FRotator LookAtRotation = Direction.Rotation();
		RotateFunction(LookAtRotation, DeltaTime, 10.f);
	}
	

}

void ATowerPawn::LookAtPawn(APawn* OtherPawn)
{
	CurrentTarget = OtherPawn;
}