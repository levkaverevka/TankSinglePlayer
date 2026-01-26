// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameState.h"
#include "HealthComponent.h"

void AMyGameState::TurretDeath(AActor* DeadActor, UHealthComponent* HealthComp)
{
	OnTurretDeath.Broadcast(DeadActor);
	UE_LOG(LogTemp, Warning, TEXT("Game state TurretDeath"));
}
