// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "TowerPawn.h"

void AMyGameModeBase::BeginPlay()
{
    Super::BeginPlay();
    //ATowerPawn->OnTowerSpawn.AddDynamic(this, &AMyGameModeBase::UpdatedEnemyCount());
}

void  AMyGameModeBase::AddEnemyCount()
{
    EnemyCount++;;
    UE_LOG(LogTemp, Warning, TEXT("Enemy count: %d"), EnemyCount);
}

void AMyGameModeBase::DecreaseEnemyCount()
{
    if (EnemyCount != 0)
    {
        EnemyCount--;;
        UE_LOG(LogTemp, Warning, TEXT("Enemy count: %d"), EnemyCount);
        if (EnemyCount == 0)
        {
            OnWinGame.Broadcast();
        }
    }
    else
    {
        OnWinGame.Broadcast();
    }
}
