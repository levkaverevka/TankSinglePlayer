// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurretPawn.h"
#include "TowerPawn.generated.h"

class UPawnSensingComponent;
/**
 * 
 */
UCLASS()
class FOXTOWERPROJ_API ATowerPawn : public ATurretPawn
{
	GENERATED_BODY()

public:
	ATowerPawn();
	
protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void LookAtPawn(APawn* OtherPawn);

	UFUNCTION()
	void OnSeePawn(APawn* OtherPawn);

	UFUNCTION()
	void Fire();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Awareness")
	TObjectPtr<UPawnSensingComponent> PawnSensor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Awareness")
	float FireInterval = 0.5f;

	FTimerHandle FTimer;
	APawn* CurrentTarget = nullptr;

};
