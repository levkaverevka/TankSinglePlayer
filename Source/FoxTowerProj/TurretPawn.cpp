// Fill out your copyright notice in the Description page of Project Settings.


#include "TurretPawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Pawn.h"

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
	TurretMesh->SetupAttachment(CapsuleComponent);

	ProjectileSpawnComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Component"));
	ProjectileSpawnComponent->SetupAttachment(CapsuleComponent);
}

// Called every frame
//void ATurretPawn::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}
//
//// Called to bind functionality to input
//void ATurretPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
//{
////	Super::SetupPlayerInputComponent(PlayerInputComponent);
//
//}

