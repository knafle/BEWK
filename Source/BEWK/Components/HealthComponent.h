// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnComponentOutOfHealth, const AActor*, DamageCauser);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCurrentHealthChanged);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BEWK_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()


public:	
	// Sets default values for this component's properties
	UHealthComponent();

	UFUNCTION(BlueprintCallable, Category = "Health")
	inline float GetCurrentHealth() const { return CurrentHealth; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	inline bool GetIsDead() const { return bIsDead; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	void Revive();

	void TakeDamage(float Damage, struct FDamageEvent const & DamageEvent, AController* InstigatedBy, AActor* DamageCauser);

	UFUNCTION(BlueprintCallable)
	float GetCurrentHealthProgress() const { return (InitialHealth > 0.f ? CurrentHealth / InitialHealth : 0.f); }

	float GetMaxHealth() const { return InitialHealth; }

	void SetMaxHealth(float Health) { InitialHealth = Health; CurrentHealth = Health; }

	inline bool const IsLowHealth() { return CurrentHealth < LowHealth; }

	UFUNCTION(BlueprintCallable)
	float Heal(float Value);

	UPROPERTY(BlueprintAssignable, Transient, Category = "Dead Delegation")
	FOnComponentOutOfHealth OnComponentOutOfHealth;

	UPROPERTY(BlueprintAssignable, Transient)
	FOnCurrentHealthChanged OnCurrentHealthChanged;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float InitialHealth = 3000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float LowHealthPercent = 20;

	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UPROPERTY(Transient)
	float LowHealth;

	UPROPERTY(Transient)
	float CurrentHealth;

	UPROPERTY(Transient)
	bool bIsDead;
		
};
