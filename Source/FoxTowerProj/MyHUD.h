// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyHUD.generated.h"

/**
 * 
 */
class UUserWidget;
class UHealthComponent;
UCLASS()
class FOXTOWERPROJ_API AMyHUD : public AHUD
{
	GENERATED_BODY()
	
	public:
		virtual void BeginPlay() override;
		UUserWidget* EndScreenWidget = nullptr;

		UFUNCTION(BlueprintCallable)
		void ShowLoseScreen(AActor* DeadActor, UHealthComponent* HealthComp);

		UFUNCTION(BlueprintCallable)
		void ShowWinScreen();

		UFUNCTION(BlueprintCallable)
		void RemoveEndScreen();

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> LoseWidgetClass;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> WinWidgetClass;

		UPROPERTY()
		UHealthComponent* HealthComponent;
};
