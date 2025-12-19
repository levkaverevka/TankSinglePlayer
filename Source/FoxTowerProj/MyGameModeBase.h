// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnWinGame);
UCLASS()
class FOXTOWERPROJ_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
	public:
		virtual void BeginPlay() override; 
		int EnemyCount = 0;
		UFUNCTION()
		void  AddEnemyCount();
		UFUNCTION()
		void  DecreaseEnemyCount();

		UPROPERTY(BlueprintAssignable, Category = "Game state")
		FOnWinGame OnWinGame;
};
