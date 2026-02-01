// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthWidget.h"
#include "HealthComponent.h"
#include <Components/ProgressBar.h>

void UHealthWidget::NativeConstruct()
{
	Super::NativeConstruct();
	/*APlayerController* PC = GetOwningPlayer();
	if (!PC)
	{
		UE_LOG(LogTemp, Warning, TEXT("Owning player is nullptr"));
		return;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Owning player exists"));
	}*/
	
}

void UHealthWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (HealthComp)
	{
		HealthComp->OnDamage.RemoveDynamic(this, &UHealthWidget::OnHealthChanged);
	}
}

void UHealthWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (APawn* Pawn = GetOwningPlayer()->GetPawn())
	{
		UE_LOG(LogTemp, Warning, TEXT("Pawn from player exists"));

		HealthComp = Pawn->GetComponentByClass<UHealthComponent>();
		if (HealthComp)
		{
			HealthComp->OnDamage.AddDynamic(this, &UHealthWidget::OnHealthChanged);
			UE_LOG(LogTemp, Warning, TEXT("HealthComp exists"));
		}
	}
}

void UHealthWidget::OnHealthChanged(AActor* DamagedActor, float CurrentHealth)
{
	float Percent = CurrentHealth / HealthComp->GetMaxHealth();
	HealthBar->SetPercent(Percent);
	OnHealthUpdated.Broadcast(DamagedActor, CurrentHealth);
	UE_LOG(LogTemp, Warning, TEXT("HealthWidget Broadcasted OnHealthUpdated"));
}
