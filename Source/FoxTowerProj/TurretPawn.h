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

DECLARE_LOG_CATEGORY_EXTERN(DeathLog, Warning, All);

UCLASS(ABSTRACT)
class FOXTOWERPROJ_API ATurretPawn : public APawn
{
	GENERATED_BODY()

public:
	ATurretPawn();

	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;
	void Fire();

protected:

	void RotateFunction(const FRotator& LookAtRotation, float DeltaTime, float InterpSpeed);
	void SpawnProjectile();

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

	UFUNCTION()
	static TArray<FName> GetMaterialSlotOptions();

	UFUNCTION()
	virtual void OnDeathStarted(AActor* DeadActor, UHealthComponent* HealthComp);


};
