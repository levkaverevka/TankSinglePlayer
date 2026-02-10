// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyAmount.h"
#include "MyGameModeBase.h"
#include "Components/TextBlock.h"

void UEnemyAmount::NativeDestruct()
{
	Super::NativeDestruct();
	if (AMyGameModeBase* GM = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		GM->OnUpdateEnemyCount.RemoveDynamic(this, &UEnemyAmount::EnemyCountChanged);
	}
}

void UEnemyAmount::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (AMyGameModeBase* GM = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		EnemyCountChanged(GM->GetEnemyCount());
		GM->OnUpdateEnemyCount.AddDynamic(this, &UEnemyAmount::EnemyCountChanged);
	}
}

void UEnemyAmount::EnemyCountChanged(int NewEnemyCount)
{
	EnemyAmount->SetText(FText::AsNumber(NewEnemyCount));
	OnEnemyCountChanged.Broadcast(NewEnemyCount);
}
