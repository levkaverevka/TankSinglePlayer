// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthWidget.h"
#include "HealthComponent.h"
#include <Components/ProgressBar.h>

void UHealthWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (APawn* Pawn = GetOwningPlayer()->GetPawn())
	{
		HealthComp = Pawn->GetComponentByClass<UHealthComponent>();
		if (HealthComp)
		{
			HealthComp->OnDamage.AddDynamic(this, &UHealthWidget::OnHealthChanged);
		}
	}

}

void UHealthWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (HealthComp)
	{
		HealthComp->OnDamage.RemoveDynamic(this, &UHealthWidget::OnHealthChanged);
	}
}

void UHealthWidget::OnHealthChanged(AActor* DamagedActor, float CurrentHealth)
{
	float Percent = CurrentHealth / HealthComp->GetMaxHealth();
	HealthBar->SetPercent(Percent);
	OnHealthUpdated.Broadcast(DamagedActor, CurrentHealth);
}
