// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExplosionFX.generated.h"

class UNiagaraComponent;
UCLASS()
class FOXTOWERPROJ_API AExplosionFX : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExplosionFX();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "VFX")
	UNiagaraComponent* NiagaraExplosion;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Time to start")
	float TimeToDestroy = 5.f;
private:
	FTimerHandle DestroyTimer;
	void DestroySelf();

};
