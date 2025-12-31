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

	ShowStartScreen();
	if (AMyGameModeBase* GM = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		GM->OnWinGame.AddUObject(this, &AMyHUD::ShowWinScreen);
		GM->OnLoseGame.AddUObject(this, &AMyHUD::ShowLoseScreen);
		GM->OnRestart.AddUObject(this, &AMyHUD::RemoveEndScreen);
		GM->OnGameStart.AddUObject(this, &AMyHUD::HideStartScreen);
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

void AMyHUD::ShowStartScreen()
{
	if (!StartWidget)
	{
		StartWidget = CreateWidget(GetOwningPlayerController(), StartWidgetClass);
		StartWidget->AddToViewport();
	}
}

void AMyHUD::HideStartScreen()
{
	if (StartWidget)
	{
		StartWidget->RemoveFromParent();
		StartWidget = nullptr;
	}
}

