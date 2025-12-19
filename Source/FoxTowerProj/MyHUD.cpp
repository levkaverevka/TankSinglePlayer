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
	if (APlayerController* PC = GetOwningPlayerController())
	{
		if (APawn* Pawn = PC->GetPawn())
		{
			HealthComponent = Pawn->FindComponentByClass<UHealthComponent>();
		}
	}
	if (HealthComponent)
	{
		HealthComponent->OnDeath.AddDynamic(this, &AMyHUD::ShowLoseScreen);
	}
	if (AMyGameModeBase* GM = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		GM->OnWinGame.AddDynamic(this, &AMyHUD::ShowWinScreen);
	}
}

void AMyHUD::ShowLoseScreen(AActor* DeadActor, UHealthComponent* HealthComp)
{

	if (Cast<ATankPawn>(DeadActor))
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

