// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CameraShakeComponent.generated.h"


class AProjectile;
class ATurretPawn;
class UHealthComponent;
class AMyPlayerController;

DECLARE_LOG_CATEGORY_EXTERN(ShakeInfo, Log, All);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FOXTOWERPROJ_API UCameraShakeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCameraShakeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Camera Shake")
	TSubclassOf<UCameraShakeBase> OnShootShakeClass;

	UPROPERTY(EditDefaultsOnly, Category = "Camera Shake")
	TSubclassOf<UCameraShakeBase> OnAnyDeathClass;

	UFUNCTION()
	void ShootShake(AProjectile* Projectile, ATurretPawn* Owner);

	UFUNCTION()
	void DeathShake(AActor* DeadActor);

private:
	AMyPlayerController* PC = nullptr;
};
