// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TurretPawn.generated.h"

class UCapsuleComponent;
class StaticMeshComponent;
class USceneComponent;
class UInputComponent;
class UMaterialInstanceDynamic;
class UHealthComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UAudioComponent;
class AProjectile;
class APawn;


DECLARE_LOG_CATEGORY_EXTERN(DeathLog, Warning, All);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnProjectileFired, AProjectile*, Projectile, ATurretPawn*, Owner);

UCLASS(ABSTRACT)
class FOXTOWERPROJ_API ATurretPawn : public APawn
{
	GENERATED_BODY()

public:
	ATurretPawn();

	UPROPERTY(BlueprintAssignable)
	FOnProjectileFired OnProjectileFired;
	
	virtual void PostInitializeComponents() override;
	void Fire();

	USceneComponent* GetProjectileSpawnComponent() const
	{
		return ProjectileSpawnComponent.Get();
	}
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> TurretMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> ProjectileSpawnComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UHealthComponent* HealthComponent;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> Dynamic_MI_Ref;

	UPROPERTY(EditAnywhere, Category = "Team", meta = (GetOptions = "GetMaterialSlotOptions"))
	FName TeamMaterialSlotName;

	UPROPERTY(EditAnywhere, Category = "Team")
	FName MaterialParameterName;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Team")
	FLinearColor TeamMaterialColor = FLinearColor::White;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile")
	TSubclassOf<class AProjectile> Projectile;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* MuzzleSmokeFX;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly, Category = "VFX")
	UNiagaraComponent* ExplosionComponent;

	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "SFX")
	USoundBase* ShootSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SFX")
	USoundBase* DeathSound;

	UFUNCTION()
	void RotateFunction(const FRotator& LookAtRotation, float DeltaTime, float InterpSpeed);

	UFUNCTION()
	void SpawnProjectile();

	UFUNCTION()
	static TArray<FName> GetMaterialSlotOptions();

	UFUNCTION()
	virtual void OnDeathStarted(AActor* DeadActor, UHealthComponent* HealthComp);

private:
	/*UPROPERTY(EditDefaultsOnly, Category = "Death")
	float DestroyDelay = 2.0f;*/
};
