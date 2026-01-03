// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosionFX.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
// Sets default values
AExplosionFX::AExplosionFX()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	NiagaraExplosion = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Explosion FX Component"));
	NiagaraExplosion->SetRelativeRotation(FRotator(90.f, 0.f, 0.f));
	SetRootComponent(NiagaraExplosion);
}

// Called when the game starts or when spawned
void AExplosionFX::BeginPlay()
{
	Super::BeginPlay();
	NiagaraExplosion->Activate();
	GetWorldTimerManager().SetTimer(DestroyTimer, this, &AExplosionFX::DestroySelf, TimeToDestroy, false);
}

void AExplosionFX::DestroySelf()
{
	Destroy();
}


