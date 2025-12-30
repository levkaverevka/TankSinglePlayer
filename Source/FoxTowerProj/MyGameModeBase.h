// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

class UHealthComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWinGame);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLoseGame);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnRestart);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnGameStart);

UCLASS()
class FOXTOWERPROJ_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	public:
		UFUNCTION()
		void  AddEnemyCount();
		UFUNCTION()
		void  DecreaseEnemyCount();

		UPROPERTY(BlueprintAssignable, Category = "Game state")
		FOnWinGame OnWinGame;

		UPROPERTY(BlueprintAssignable, Category = "Game state")
		FOnLoseGame OnLoseGame;

		UPROPERTY(BlueprintAssignable, Category = "Game state")
		FOnRestart OnRestart;

		UPROPERTY(BlueprintAssignable, Category = "Game state")
		FOnGameStart OnGameStart;
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
