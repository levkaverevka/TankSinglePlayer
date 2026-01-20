// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UParticleSystem;
UCLASS()
class FOXTOWERPROJ_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UProjectileMovementComponent> ProjMovement;
protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> ProjectileMesh;

	UPROPERTY(EditDefaultsOnly,Category = "VFX")
	UParticleSystem* OnHitVFX;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Damage")
	float Damage = 25.f;

	UFUNCTION()
	void OnComponentHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

public:	

};
