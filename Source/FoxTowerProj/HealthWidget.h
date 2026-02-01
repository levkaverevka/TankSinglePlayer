// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthWidget.generated.h"

/**
 * 
 */

class UHealthComponent;
class UProgressBar;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthUpdated, AActor*, DamagedActor, float, CurrentHealth);

UCLASS()
class FOXTOWERPROJ_API UHealthWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable, Category = "Health")
	FOnHealthUpdated OnHealthUpdated;
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeOnInitialized();

	UFUNCTION()
	void OnHealthChanged(AActor* DamagedActor, float CurrentHealth);

	/*UDUNCTION(AActor* DamagedActor, float CurrentHealth, ESenderTypes Type)*/
private:
	UPROPERTY()
	UHealthComponent* HealthComp;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;
};
