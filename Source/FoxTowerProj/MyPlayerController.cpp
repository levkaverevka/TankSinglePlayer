// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "MyHUD.h"
#include "MyGameModeBase.h"

void AMyPlayerController::SetPlayerEnableState(bool bEnableState)
{
	if (bEnableState)
	{
		GetPawn()->EnableInput(this);
		bShowMouseCursor = true;
		bEnableClickEvents = true;
		bEnableMouseOverEvents = true;
	}
	else
	{
		GetPawn()->DisableInput(this);
		bShowMouseCursor = true;
		bEnableClickEvents = true;
		bEnableMouseOverEvents = true;
	}
}

void AMyPlayerController::OnGameStarted()
{
	SetPlayerEnableState(true);
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetPlayerEnableState(false);
	if (AMyGameModeBase* GM = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode()))
	{
		GM->OnGameStart.AddUObject(this, &AMyPlayerController::OnGameStarted);
	}

}

