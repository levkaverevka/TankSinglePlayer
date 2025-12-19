// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameModeBase.h"
#include "MyHUD.h"

void AMyPlayerController::SetPlayerEnableState(bool bEnableState)
{
	if (bEnableState)
	{
		GetPawn()->EnableInput(this);
		bShowMouseCursor = true;
	}
	else
	{
		GetPawn()->DisableInput(this);
		bShowMouseCursor = true;
	}
}

void AMyPlayerController::RestartCurrentLevel()
{
	if (UWorld* World = GetWorld()) 
	{
		const FName CurrentLevelName(*World->GetName());
		UGameplayStatics::OpenLevel(this, CurrentLevelName);
		if (AMyHUD* HUD = GetHUD<AMyHUD>())
		{
			HUD->RemoveEndScreen();
		}
	}
		
}

