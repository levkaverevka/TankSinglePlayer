// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

class UHealthComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpdateEnemyCount, int, EnemyCount);
UCLASS()
class FOXTOWERPROJ_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	public:

		FSimpleMulticastDelegate OnWinGame;
		FSimpleMulticastDelegate OnLoseGame;
		FSimpleMulticastDelegate OnRestart;
		FSimpleMulticastDelegate OnGameStart;

		UPROPERTY(BlueprintAssignable)
		FOnUpdateEnemyCount OnUpdateEnemyCount;

		UFUNCTION(BlueprintPure)
		int GetEnemyCount()
		{
			return EnemyCount;
		}

		UFUNCTION()
		void UpdateEnemyCount(int NewEnemyCount);

		UFUNCTION()
		void  AddEnemyCount();
		UFUNCTION()
		void  DecreaseEnemyCount();

		UPROPERTY(BlueprintReadWrite,EditAnywhere, Category = "Time to start")
		float TimeToStart = 3.f;
	protected:
		virtual void BeginPlay() override;

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

		UPROPERTY()
		int EnemyCount = 0;
};
