// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretPawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Projectile.h"
#include "ExplosionFX.h"
#include "HealthComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include <NiagaraFunctionLibrary.h>


DEFINE_LOG_CATEGORY(DeathLog);
// Sets default values
ATurretPawn::ATurretPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule root"));
	SetRootComponent(CapsuleComponent); 

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComponent);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Component"));
	ProjectileSpawnComponent->SetupAttachment(TurretMesh);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));

	MuzzleSmokeFX = CreateDefaultSubobject<UNiagaraSystem>(TEXT("Muzzle Smoke VFX"));
}


TArray<FName> ATurretPawn::GetMaterialSlotOptions()
{
	return
	{
		FName("Team_Material"),
		FName("_Base_Material")
	};
		
}

void ATurretPawn::OnDeathStarted(AActor* DeadActor, UHealthComponent* HealthComp)
{
	UE_LOG(DeathLog, Warning, TEXT("%s, is dead,  (HealthComp: %s) "), *DeadActor->GetName(), *HealthComp->GetName());
	if (Explosion)
	{
		GetWorld()->SpawnActor<AExplosionFX>(Explosion, GetActorTransform());
	}
	Destroy();
}

void ATurretPawn::RotateFunction(const FRotator& PredictedRotation, float DeltaTime, float InterpSpeed)
{
	FRotator TurretRotation = FRotator(0.f, PredictedRotation.Yaw, 0.f);
	FRotator InterpolatedRotation = FMath::RInterpTo(TurretMesh->GetRelativeRotation(), TurretRotation, DeltaTime, InterpSpeed);
	TurretMesh->SetRelativeRotation(InterpolatedRotation);;
}

void ATurretPawn::Fire()
{
	SpawnProjectile();
	if (MuzzleSmokeFX)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), MuzzleSmokeFX, ProjectileSpawnComponent->GetComponentLocation(), ProjectileSpawnComponent->GetComponentRotation(), FVector(0.1f));
	}
}

void ATurretPawn::SpawnProjectile()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	GetWorld()->SpawnActor<AActor>(Projectile.Get(), ProjectileSpawnComponent->GetComponentLocation(), ProjectileSpawnComponent->GetComponentRotation(), SpawnParams);
}

void ATurretPawn::BeginPlay()
{
	Super::BeginPlay();
	HealthComponent->OnDeath.AddDynamic(this, &ATurretPawn::OnDeathStarted);
}

void ATurretPawn::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	auto ApplyTeamColor = [this](UStaticMeshComponent* Mesh)
		{
			int32 SlotIndex = Mesh->GetMaterialIndex(TeamMaterialSlotName);
			if (SlotIndex != INDEX_NONE)
			{
				Dynamic_MI_Ref = Mesh->CreateAndSetMaterialInstanceDynamic(SlotIndex);
				if (Dynamic_MI_Ref)
				{
					Dynamic_MI_Ref->SetVectorParameterValue(MaterialParameterName, TeamMaterialColor);
				}
			}
		};
	ApplyTeamColor(BaseMesh);
	ApplyTeamColor(TurretMesh);
}

