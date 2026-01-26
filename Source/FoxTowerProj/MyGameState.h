// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MyGameState.generated.h"

/**
 * 
 */
class UHealthComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTurretDeath, AActor*, DeadActor);
UCLASS()
class FOXTOWERPROJ_API AMyGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnTurretDeath OnTurretDeath;

	UFUNCTION()
	void TurretDeath(AActor* DeadActor, UHealthComponent* HealthComp);
};
