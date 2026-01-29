// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "Blueprint/UserWidget.h"
#include "HealthComponent.h"
#include "TankPawn.h"
#include "TowerPawn.h"
#include "MyGameModeBase.h"
#include "HealthWidget.h"


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
	HealthWidget = CreateWidget<UHealthWidget>(GetWorld(), HealthWidgetClass);
	if (HealthWidget)
	{
		HealthWidget->OnHealthUpdated.AddDynamic(this, &AMyHUD::ShowHealthBar);
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

void AMyHUD::ShowHealthBar(AActor* DamagedActor, float CurrentHealth)
{
	UE_LOG(LogTemp, Warning, TEXT("ShowHealthbar HUD Works"));

	if (HealthWidget)
	{
		HealthWidget->AddToViewport(5);
		UE_LOG(LogTemp, Warning, TEXT("ADd to viewport HUD Works"));

	}
}
