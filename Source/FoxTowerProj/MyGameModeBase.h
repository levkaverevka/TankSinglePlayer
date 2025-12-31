// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

class UHealthComponent;

UCLASS()
class FOXTOWERPROJ_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	public:

		FSimpleMulticastDelegate OnWinGame;
		FSimpleMulticastDelegate OnLoseGame;
		FSimpleMulticastDelegate OnRestart;
		FSimpleMulticastDelegate OnGameStart;

		UFUNCTION()
		void  AddEnemyCount();
		UFUNCTION()
		void  DecreaseEnemyCount();

		UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Time to start")
		float TimeToStart = 3.f;
	protected:
		virtual void BeginPlay() override;

		int EnemyCount = 0;

		UPROPERTY()
		UHealthComponent* HealthComponent;

		UFUNCTION()
		void PlayerIsDead(AActor* DeadActor, UHealthComponent* HealthComp);

		UFUNCTION(BlueprintCallable)
		void RestartCurrentLevel();

		UFUNCTION()
		void GameStart();

	private:
		FTimerHandle StartDelayTimer;
};
