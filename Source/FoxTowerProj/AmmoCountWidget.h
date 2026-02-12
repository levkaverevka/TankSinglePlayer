// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AmmoCountWidget.generated.h"

/**
 * 
 */
class UTextBlock;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAmmoChanged, int32, AmmoCount);
UCLASS()
class FOXTOWERPROJ_API UAmmoCountWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable)
	FOnAmmoChanged OnAmmoChanged;
protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurrentAmmo;

	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void NativeOnInitialized();

	UFUNCTION()
	void UpdateAmmoCount(int32 AmmoCount);
};
