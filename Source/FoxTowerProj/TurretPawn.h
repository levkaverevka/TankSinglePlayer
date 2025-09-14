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

UCLASS(ABSTRACT)
class FOXTOWERPROJ_API ATurretPawn : public APawn
{
	GENERATED_BODY()

public:
	ATurretPawn();

protected:


	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Capsule Component")
	TObjectPtr<UCapsuleComponent> CapsuleComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base Mesh")
	TObjectPtr<UStaticMeshComponent> BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Turret Mesh Component")
	TObjectPtr<UStaticMeshComponent> TurretMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Turret Mesh Component")
	TObjectPtr<USceneComponent> ProjectileSpawnComponent;

	UPROPERTY()
	TObjectPtr<UMaterialInstanceDynamic> Dynamic_MI_Ref;

	UPROPERTY(EditAnywhere, Category = "Team", meta = (GetOptions = "GetMaterialSlotOptions"))
	FName TeamMaterialSlotName;

	UPROPERTY(EditAnywhere, Category = "Team")
	FName MaterialParameterName;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Team")
	FLinearColor TeamMaterialColor = FLinearColor::White;

	UFUNCTION()
	static TArray<FName> GetMaterialSlotOptions();

	UFUNCTION()
	void PostInitComponents(UStaticMeshComponent* Mesh);


};
