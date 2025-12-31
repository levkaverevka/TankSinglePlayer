// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class FOXTOWERPROJ_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	public:

		UFUNCTION(BlueprintCallable)
		void SetPlayerEnableState(bool bEnableState);

		UFUNCTION()
		void OnGameStarted();

	protected:
		virtual void BeginPlay() override;
	private:
};
