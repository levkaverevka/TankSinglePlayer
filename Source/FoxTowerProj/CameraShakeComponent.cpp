// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraShakeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyPlayerController.h"
#include "TurretPawn.h"
#include "TankPawn.h"
#include "Projectile.h"
#include "HealthComponent.h"


// Sets default values for this component's properties
UCameraShakeComponent::UCameraShakeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UCameraShakeComponent::BeginPlay()
{
	Super::BeginPlay();

	PC = Cast<AMyPlayerController>(GetOwner());

	if (PC)
	{
		if (ATankPawn* TankPawn = Cast<ATankPawn>(PC->GetPawn()))
		{
			TankPawn->OnProjectileFired.AddDynamic(this, &UCameraShakeComponent::ShootShake);
			UE_LOG(LogTemp, Warning, TEXT("PC: %s, TankPawn: %s"), PC ? TEXT("Valid") : TEXT("NULL"), TankPawn ? TEXT("Valid") : TEXT("NULL"))
		}
	}
	

}

void UCameraShakeComponent::ShootShake(AProjectile* Projectile, ATurretPawn* Owner)
{
	UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0)->StartCameraShake(OnShootShakeClass);
	UE_LOG(LogTemp, Warning, TEXT("ShootShake called, Class: %s"), OnShootShakeClass ? TEXT("Valid") : TEXT("NULL"));
}

void UCameraShakeComponent::DeathShake(AActor* DeadActor, UHealthComponent* HealthComp)
{
	if (PC)
	{
		PC->ClientStartCameraShake(OnAnyDeathClass);
		UE_LOG(LogTemp, Warning, TEXT("OnAnyDeathClass called, Class: %s"), OnAnyDeathClass ? TEXT("Valid") : TEXT("NULL"));
	}
}

