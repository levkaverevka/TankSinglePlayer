// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"
#include "TowerPawn.h"
#include "HealthComponent.h"
#include "Kismet/GameplayStatics.h"


void AMyGameModeBase::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
    {
        if (APawn* Pawn = PC->GetPawn())
        {
            HealthComponent = Pawn->FindComponentByClass<UHealthComponent>();
        }
    }
    if (HealthComponent)
    {
        HealthComponent->OnDeath.AddDynamic(this, &AMyGameModeBase::PlayerIsDead);
    }
}

void AMyGameModeBase::PlayerIsDead(AActor* DeadActor, UHealthComponent* HealthComp)
{
    OnLoseGame.Broadcast();
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

void AMyGameModeBase::RestartCurrentLevel()
{
    if (UWorld* World = GetWorld())
    {
        const FName CurrentLevelName(*World->GetName());
        UGameplayStatics::OpenLevel(this, CurrentLevelName);
        OnRestart.Broadcast();
    }
}
