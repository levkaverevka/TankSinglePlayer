// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TurretPawn.generated.h"

class UCapsuleComponent;
class StaticMeshComponent;
class USceneComponent;
class UInputComponent;

UCLASS()
class FOXTOWERPROJ_API ATurretPawn : public APawn
{
	GENERATED_BODY()

public:
	ATurretPawn();

	/*virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;*/

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Capsule Component")
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base Mesh")
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Turret Mesh Component")
	TObjectPtr<UStaticMeshComponent> TurretMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Turret Mesh Component")
	TObjectPtr<USceneComponent> ProjectileSpawnComponent;

};
