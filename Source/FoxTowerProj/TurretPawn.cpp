// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretPawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Projectile.h"


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
}


TArray<FName> ATurretPawn::GetMaterialSlotOptions()
{
	return
	{
		FName("Team_Material"),
		FName("_Base_Material")
	};
		
}

void ATurretPawn::RotateFunction(const FRotator& LookAtRotation, float DeltaTime, float InterpSpeed)
{
	FRotator TurretRotation = FRotator(0.f, LookAtRotation.Yaw, 0.f);
	FRotator InterpolatedRotation = FMath::RInterpTo(TurretMesh->GetRelativeRotation(), TurretRotation, DeltaTime, 7.f);
	TurretMesh->SetRelativeRotation(InterpolatedRotation);;
}

void ATurretPawn::Fire()
{
	/*FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;*/
	SpawnProjectile();
}

void ATurretPawn::SpawnProjectile()
{
	GetWorld()->SpawnActor<AActor>(Projectile.Get(), ProjectileSpawnComponent->GetComponentLocation(), ProjectileSpawnComponent->GetComponentRotation());
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
