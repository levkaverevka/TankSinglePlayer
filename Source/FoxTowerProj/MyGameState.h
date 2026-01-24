// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameState.generated.h"

/**
 * 
 */
class UHealthComponent;
UCLASS()
class FOXTOWERPROJ_API AMyGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	FSimpleMulticastDelegate OnTurretDeath;

	UFUNCTION()
	void TurretDeath(AActor* DeadActor, UHealthComponent* HealthComp);
};
