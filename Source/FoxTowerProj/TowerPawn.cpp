// Fill out your copyright notice in the Description page of Project Settings.


#include "TowerPawn.h"
#include "Perception/PawnSensingComponent.h"
#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "MyGameModeBase.h"

ATowerPawn::ATowerPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	PawnSensor = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Awareness"));
	TurretMesh->SetUsingAbsoluteRotation(true);
};

void ATowerPawn::BeginPlay()
{
	Super::BeginPlay();
	if (AMyGameModeBase* GM = GetWorld()->GetAuthGameMode<AMyGameModeBase>())
	{
		GM->AddEnemyCount();
	}
	
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

	GetWorldTimerManager().SetTimer(FireTimer, this, &ATurretPawn::Fire, FireInterval, true);
}

void ATowerPawn::NullPawn()
{
	CurrentTarget = nullptr;
	GetWorldTimerManager().ClearTimer(FireTimer);
}

void ATowerPawn::OnDeathStarted(AActor* DeadActor, UHealthComponent* HealthComp)
{
	Super::OnDeathStarted(DeadActor, HealthComp);
	if (AMyGameModeBase* GM = GetWorld()->GetAuthGameMode<AMyGameModeBase>())
	{
		GM->DecreaseEnemyCount();
	}
}


void ATowerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	if (CurrentTarget)
	{
		FVector TargetLocation = CurrentTarget->GetActorLocation();
		FVector MuzlleLocation = TurretMesh->GetComponentLocation();
		FVector Direction = TargetLocation - TurretMesh->GetComponentLocation();
		const AProjectile* DefaultProj = Projectile.GetDefaultObject();
		float ProjSpeed = DefaultProj->GetProjMovement()->InitialSpeed;
		FVector TargetVelocity = CurrentTarget->GetVelocity();
		float Distance = Direction.Size();
		float TimeToHit = Distance / ProjSpeed;
		FVector PredictedLocation = TargetLocation + TargetVelocity * TimeToHit * 10.f;
		FRotator PredictedRotation = (PredictedLocation - MuzlleLocation).Rotation();
		RotateTurretFunction(PredictedRotation, DeltaTime, 100.f);
	}

}

void ATowerPawn::LookAtPawn(APawn* OtherPawn)
{
	CurrentTarget = OtherPawn;
}