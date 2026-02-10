// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoCountWidget.h"
#include "Components/TextBlock.h"
#include "TankPawn.h"
#include "MyPlayerController.h"


void UAmmoCountWidget::NativeConstruct()
{

}

void UAmmoCountWidget::NativeDestruct()
{
	Super::NativeDestruct();
	if (AMyPlayerController* PC = Cast<AMyPlayerController>(GetOwningPlayer()))
	{
		if (ATankPawn* Pawn = Cast<ATankPawn>(PC->GetPawn()))
		{
			Pawn->OnTankFired.RemoveDynamic(this, &UAmmoCountWidget::UpdateAmmoCount);
		}
	}
}

void UAmmoCountWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (AMyPlayerController* PC = Cast<AMyPlayerController>(GetOwningPlayer()))
	{
		if (ATankPawn* Pawn = Cast<ATankPawn>(PC->GetPawn()))
		{
			Pawn->OnTankFired.AddDynamic(this, &UAmmoCountWidget::UpdateAmmoCount);
		}
	}
}

void UAmmoCountWidget::UpdateAmmoCount(int32 AmmoCount)
{
	if (CurrentAmmo)
	{
		CurrentAmmo->SetText(FText::AsNumber(AmmoCount));
		OnAmmoChanged.Broadcast(AmmoCount);
	}
}
