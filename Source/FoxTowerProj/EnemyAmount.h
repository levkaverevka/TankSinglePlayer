// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EnemyAmount.generated.h"

/**
 * 
 */
class UTextBlock;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEnemyCountChanged, int, NewEnemyCount);
UCLASS()
class FOXTOWERPROJ_API UEnemyAmount : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable)
	FOnEnemyCountChanged OnEnemyCountChanged;

protected:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* EnemyAmount;

	virtual void NativeDestruct() override;
	virtual void NativeOnInitialized();

	UFUNCTION()
	void EnemyCountChanged(int NewEnemyCount);

};
