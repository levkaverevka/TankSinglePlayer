// Fill out your copyright notice in the Description page of Project Settings.


#include "SFX_Component.h"
#include "TurretPawn.h"
#include "Projectile.h"
#include "UObject/Field.h"
#include "TowerPawn.h"
#include "TankPawn.h"
#include "Components/AudioComponent.h"
#include "Kismet/GameplayStatics.h"
#include "MyPlayerController.h"


// Sets default values for this component's properties
USFX_Component::USFX_Component()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void USFX_Component::BeginPlay()
{
	Super::BeginPlay();

	if (ATurretPawn* Initiator = Cast<ATurretPawn>(GetOwner()))
	{
		Initiator->OnProjectileFired.AddDynamic(this, &USFX_Component::GetProjectile);
	}
}

void USFX_Component::GetProjectile(AProjectile* Projectile, ATurretPawn* Owner)
{
	Projectile->OnActorHit.AddDynamic(this, &USFX_Component::PlaySound);
}

void USFX_Component::PlaySound(AActor* SelfActor,AActor* OtherActor,FVector NormalImpulse,const FHitResult& Hit)
{
	UGameplayStatics::PlaySoundAtLocation(this, HitSound, Hit.ImpactPoint);
	AActor* Owner = GetOwner();
	if (OtherActor->IsA(ATurretPawn::StaticClass()))
	{
		if (OtherActor != Owner)
		{
			if (AMyPlayerController* PC = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController()))
			{
				if (PC)
				{
					UGameplayStatics::PlaySound2D(this, HitIndicator);
				}
			}
		}
	}
}
