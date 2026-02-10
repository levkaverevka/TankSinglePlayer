// Fill out your copyright notice in the Description page of Project Settings.


#include "MasterWidget.h"
#include "HealthWidget.h"
#include "AmmoCountWidget.h"
#include "EnemyAmount.h"
#include "HealthComponent.h"

void UMasterWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (HealthWidget)
	{
		HealthWidget->OnHealthUpdated.AddDynamic(this, &UMasterWidget::ShowHealthBar);
		HealthWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (AmmoWidget)
	{
		AmmoWidget->OnAmmoChanged.AddDynamic(this, &UMasterWidget::ShowAmmo);
		AmmoWidget->SetVisibility(ESlateVisibility::Hidden);
	}

	if (EnemyCountWidget)
	{
		EnemyCountWidget->OnEnemyCountChanged.AddDynamic(this, &UMasterWidget::ShowEnemyCount);
		EnemyCountWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMasterWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetVisibility(ESlateVisibility::Visible);
}

void UMasterWidget::ShowHealthBar(AActor* DamagedActor, float CurrentHealth)
{
	if (HealthWidget)
	{
		HealthWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMasterWidget::HideHealthBar()
{
	if (HealthWidget)
	{
		HealthWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMasterWidget::ShowAmmo(int32 AmmoCount)
{
	if (AmmoWidget)
	{
		AmmoWidget->SetVisibility(ESlateVisibility::Visible);
	}
}

void UMasterWidget::HideAmmo()
{
	if (AmmoWidget)
	{
		AmmoWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}
void UMasterWidget::ShowEnemyCount(int32 NewEnemyCount)
{
	if (EnemyCountWidget)
	{
		EnemyCountWidget->SetVisibility(ESlateVisibility::Visible);
	}
}
void UMasterWidget::HideEnemyCount()
{
	if (EnemyCountWidget)
	{
		EnemyCountWidget->SetVisibility(ESlateVisibility::Hidden);
	}
}

