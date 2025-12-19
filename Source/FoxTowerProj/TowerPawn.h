// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TurretPawn.h"
#include "TowerPawn.generated.h"

class UPawnSensingComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTowerSpawn);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnTowerDestroyed);

UCLASS()
class FOXTOWERPROJ_API ATowerPawn : public ATurretPawn
{
	GENERATED_BODY()

public:
	ATowerPawn();
	UPROPERTY(BlueprintAssignable, Category = "Spawn")
	FOnTowerSpawn OnTowerSpawn;

	UPROPERTY(BlueprintAssignable, Category = "Spawn")
	FOnTowerSpawn OnTowerDestroyed;
	
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void LookAtPawn(APawn* OtherPawn);

	UFUNCTION()
	void OnSeePawn(APawn* OtherPawn);

	UFUNCTION()
	void NullPawn();
	
	virtual void OnDeathStarted(AActor* DeadActor, UHealthComponent* HealthComp) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Awareness")
	TObjectPtr<UPawnSensingComponent> PawnSensor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Awareness")
	float FireInterval = 0.5f;

	
	FTimerHandle FireTimer;
	FTimerHandle NullPawnTimer;
	APawn* CurrentTarget = nullptr;

};
