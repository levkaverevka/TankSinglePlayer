// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SFX_Component.generated.h"

class AProjectile;
class ATurretPawn;
class UAudioComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FOXTOWERPROJ_API USFX_Component : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USFX_Component();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SFX")
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SFX")
	USoundBase* HitIndicator;

	UFUNCTION()
	void GetProjectile(AProjectile* Projectile, ATurretPawn* Owner);

	UFUNCTION()
	void PlaySound(AActor* SelfActor,AActor* OtherActor,FVector NormalImpulse,const FHitResult& Hit);
		
};
