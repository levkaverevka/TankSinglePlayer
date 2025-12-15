// Fill out your copyright notice in the Description page of Project Settings.


#include "MyHUD.h"
#include "Blueprint/UserWidget.h"
#include "HealthComponent.h"

void AMyHUD::BeginPlay()
{
	Super::BeginPlay();
	if(APlayerController* PC = GetOwningPlayerController())
	{
		if (APawn* Pawn = PC->GetPawn())
		{
			HealthComponent = Pawn->FindComponentByClass<UHealthComponent>();
		}
	}
	if (HealthComponent)
	{
		HealthComponent->OnDeath.AddDynamic(this, &AMyHUD::ShowEndScreen);
	}
}

void AMyHUD::ShowEndScreen(AActor* DeadActor, UHealthComponent* HealthComp)
{
	if (LoseWidgetClass)
	{
		LoseWidget = CreateWidget(GetOwningPlayerController(), LoseWidgetClass);
		if (LoseWidget)
		{
			LoseWidget->AddToViewport(10);
		}
	}
}

void AMyHUD::RemoveEndScreen()
{
	if (LoseWidget)
	{
		LoseWidget->RemoveFromParent();
		LoseWidget = nullptr;
	}
}

