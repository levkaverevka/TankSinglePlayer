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
class UHealthWidget;
UCLASS()
class FOXTOWERPROJ_API AMyHUD : public AHUD
{
	GENERATED_BODY()
	
	public:

	protected:

		virtual void BeginPlay() override;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> LoseWidgetClass;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> WinWidgetClass;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> StartWidgetClass;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI")
		TSubclassOf<UUserWidget> HealthWidgetClass;

		UPROPERTY()
		UHealthComponent* HealthComponent;

		UFUNCTION(BlueprintCallable)
		void ShowLoseScreen();

		UFUNCTION(BlueprintCallable)
		void ShowWinScreen();

		UFUNCTION(BlueprintCallable)
		void RemoveEndScreen();

		UFUNCTION(BlueprintCallable)
		void ShowStartScreen();

		UFUNCTION(BlueprintCallable)
		void HideStartScreen();

		UFUNCTION(BlueprintCallable)
		void ShowHealthBar(AActor* DamagedActor, float CurrentHealth);

	private:
		UUserWidget* EndScreenWidget = nullptr;
		UUserWidget* StartWidget = nullptr;
		UHealthWidget* HealthWidget = nullptr;

};
