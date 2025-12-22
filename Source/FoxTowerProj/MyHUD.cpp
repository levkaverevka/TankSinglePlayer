// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "Blueprint/UserWidget.h"
#include "HealthComponent.h"
#include "TankPawn.h"
#include "TowerPawn.h"
#include "MyGameModeBase.h"


void AMyHUD::BeginPlay()
{
	Super::BeginPlay();
	if (AMyGameModeBase* GM = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		GM->OnWinGame.AddDynamic(this, &AMyHUD::ShowWinScreen);
		GM->OnLoseGame.AddDynamic(this, &AMyHUD::ShowLoseScreen);
		GM->OnRestart.AddDynamic(this, &AMyHUD::RemoveEndScreen);
	}
}

void AMyHUD::ShowLoseScreen()
{
	if (LoseWidgetClass)
	{
		EndScreenWidget = CreateWidget(GetOwningPlayerController(), LoseWidgetClass);
		if (EndScreenWidget)
		{
			EndScreenWidget->AddToViewport(10);
		}
	}
}

void AMyHUD::ShowWinScreen()
{
	if (WinWidgetClass)
	{
		EndScreenWidget = CreateWidget(GetOwningPlayerController(), WinWidgetClass);
		if (EndScreenWidget)
		{
			EndScreenWidget->AddToViewport(10);
		}
	}
}

void AMyHUD::RemoveEndScreen()
{
	if (EndScreenWidget)
	{
		EndScreenWidget->RemoveFromParent();
		EndScreenWidget = nullptr;
	}
}

