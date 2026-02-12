// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "Blueprint/UserWidget.h"
#include "HealthComponent.h"
#include "TankPawn.h"
#include "TowerPawn.h"
#include "MyGameModeBase.h"
#include "HealthWidget.h"
#include "AmmoCountWidget.h"
#include "EnemyAmount.h"
#include "MasterWidget.h"

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
	MasterWidget = CreateWidget<UMasterWidget>(GetOwningPlayerController(), MasterWidgetClass);
	if (MasterWidget)
	{
		MasterWidget->AddToViewport();
	}
	////HealthWidget = CreateWidget<UHealthWidget>(GetOwningPlayerController(), HealthWidgetClass);
	//if (HealthWidget)
	//{
	//	HealthWidget->OnHealthUpdated.AddDynamic(this, &AMyHUD::ShowHealthBar);
	//}
	////AmmoWidget = CreateWidget<UAmmoCountWidget>(GetOwningPlayerController(), AmmoCountWidgetClass);
	//if (AmmoWidget)
	//{
	//	AmmoWidget->OnAmmoChanged.AddDynamic(this, &AMyHUD::ShowAmmo);
	//}
	///*EnemyCountWidget = CreateWidget<UEnemyAmount>(GetOwningPlayerController(), EnemyCountWidgetClass);*/
	//if (EnemyCountWidget)
	//{
	//	EnemyCountWidget->OnEnemyCountChanged.AddDynamic(this, &AMyHUD::ShowEnemyCount);

	//}
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

//void AMyHUD::ShowHealthBar(AActor* DamagedActor, float CurrentHealth)
//{
//	if (MasterWidget)
//	{
//		MasterWidget->ShowHealthBar(DamagedActor, CurrentHealth);
//		UE_LOG(LogTemp, Warning, TEXT("ADd to viewport HUD Works"));
//		HideWidgetDelay(ESenderTypes::FromHealthWidget);
//	}
//}
//
//void AMyHUD::HideHealthBar()
//{
//	if (MasterWidget)
//	{
//		MasterWidget->HideHealthBar();
//	}
//}
//
//void AMyHUD::ShowAmmo(int32 AmmoCount)
//{
//	if (MasterWidget)
//	{
//		MasterWidget->ShowAmmo(AmmoCount);
//		HideWidgetDelay(ESenderTypes::FromTank);
//	}
//}
//
//void AMyHUD::HideAmmo()
//{
//	if (MasterWidget)
//	{
//		MasterWidget->HideAmmo();
//	}
//}
//
//void AMyHUD::ShowEnemyCount(int32 NewEnemyCount)
//{
//	if (MasterWidget)
//	{
//		MasterWidget->ShowEnemyCount(NewEnemyCount);
//		//HideWidgetDelay(ESenderTypes::FromTank);
//	}
//}
//
//void AMyHUD::HideEnemyCount()
//{
//	if (MasterWidget)
//	{
//		MasterWidget->HideEnemyCount();
//	}
//}

//void AMyHUD::HideWidgetDelay(ESenderTypes Type)
//{
//	if (Type == ESenderTypes::FromTank)
//	{
//		GetWorldTimerManager().SetTimer(WidgetDisappearDelay, this, &AMyHUD::HideAmmo, TimeToDissappear, false);
//	}
//	else if (Type == ESenderTypes::FromHealthWidget)
//	{
//		GetWorldTimerManager().SetTimer(WidgetDisappearDelay, this, &AMyHUD::HideHealthBar, TimeToDissappear, false);
//	}
//}

