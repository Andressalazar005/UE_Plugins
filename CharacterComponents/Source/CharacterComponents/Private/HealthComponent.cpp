// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

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
	CurHealth = MaxHealth;
	// ...
	
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::TakeDamage(AActor* Instigator, float Damage, FVector Location)
{
	if (CurHealth - Damage > 0)
	{
		CurHealth -= Damage;
	}
	else
	{
		OnDeath(Instigator);
	}
	OnDamageDelegateSignature.Broadcast(Location,Instigator);
}

float UHealthComponent::GetHealth()
{
	return CurHealth;
}

void UHealthComponent::OnDeath_Implementation(AActor* Instigator)
{
	OnDeathDelegateSignature.Broadcast(Instigator);
}

