// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "CoreMinimal.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = InitialHealth;
	LowHealth = CurrentHealth * LowHealthPercent / 100;
}

void UHealthComponent::Revive()
{
	bIsDead = false;
	CurrentHealth = InitialHealth;
}

void UHealthComponent::TakeDamage(float Damage, struct FDamageEvent const & DamageEvent, AController* InstigatedBy, AActor* DamageCauser)
{
	if (bIsDead)
	{
		return;
	}

	CurrentHealth -= FMath::Max(Damage, 0.0f);

	if (CurrentHealth <= 0)
	{
		CurrentHealth = 0;
		bIsDead = true;
		OnComponentOutOfHealth.Broadcast(DamageCauser);
	}

	OnCurrentHealthChanged.Broadcast();
}

float UHealthComponent::Heal(float Value)
{
	CurrentHealth = FMath::Clamp(CurrentHealth + Value, 0.f, GetMaxHealth());
	float HealedValue = FMath::Min(GetMaxHealth() - CurrentHealth, Value);
	return HealedValue;

	return 0.0f;
}


