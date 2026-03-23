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
		//GetPawn()->EnableInput(this);

		bShowMouseCursor = false;
		bEnableClickEvents = false;
		bEnableMouseOverEvents = false;

		FInputModeGameOnly InputMode;
		SetInputMode(InputMode);
	}
	else
	{
		//GetPawn()->DisableInput(this);
		bShowMouseCursor = true;
		bEnableClickEvents = true;
		bEnableMouseOverEvents = true;

		FInputModeUIOnly  InputMode;
		SetInputMode(InputMode);
	}
}

void AMyPlayerController::OnGameStarted()
{
	SetPlayerEnableState(true);
	UE_LOG(LogTemp, Warning, TEXT("OnGameStarted"));
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

