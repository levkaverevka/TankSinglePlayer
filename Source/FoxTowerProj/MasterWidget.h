// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MasterWidget.generated.h"

/**
 * 
 */
class UHealthWidget;
class UAmmoCountWidget;
class UEnemyAmount;
UCLASS()
class FOXTOWERPROJ_API UMasterWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void ShowHealthBar(AActor* DamagedActor, float CurrentHealth);

	UFUNCTION(BlueprintCallable)
	void HideHealthBar();

	UFUNCTION(BlueprintCallable)
	void ShowAmmo(int32 AmmoCount);

	UFUNCTION(BlueprintCallable)
	void HideAmmo();

	UFUNCTION(BlueprintCallable)
	void ShowEnemyCount(int32 NewEnemyCount);
	UFUNCTION(BlueprintCallable)
	void HideEnemyCount();

protected:

	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized();

	UPROPERTY(meta = (BindWidget))
	UHealthWidget* HealthWidget;

	UPROPERTY(meta = (BindWidget))
	UAmmoCountWidget* AmmoWidget;

	UPROPERTY(meta = (BindWidget))
	UEnemyAmount* EnemyCountWidget;

private:
	
};
