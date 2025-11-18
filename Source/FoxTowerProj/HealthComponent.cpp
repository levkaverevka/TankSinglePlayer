// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	//AActor* Owner = GetOwner();
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::HandleDamage);
	CurrentHealth = MaxHealth;
	
}

void UHealthComponent::HandleDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.f) return;

	CurrentHealth -= Damage;
	if (CurrentHealth <= 0.f)
	{
		CurrentHealth = 0.f;
		GetOwner()->Destroy();
	}


}


//// Called every frame
//void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
//{
//	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
//
//	/*if (CurrentHealth <= 0)
//	{
//		IsDead = true;
//	}
//
//	if (IsDead)
//	{
//		GetOwner()->Destroy();
//	}*/
//}

