// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeathDelegateSignature,AActor*,Instigator);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnDamageDelegateSignature, FVector, Location,AActor*,Instigator);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CHARACTERCOMPONENTS_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

	UPROPERTY(BlueprintAssignable)
	FOnDeathDelegateSignature OnDeathDelegateSignature;

	UPROPERTY(BlueprintAssignable)
	FOnDamageDelegateSignature OnDamageDelegateSignature;



	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void TakeDamage(AActor* Instigator, float Damage, FVector Location);
	UFUNCTION(BlueprintPure)
	float GetHealth();
	UFUNCTION(BlueprintCallable)
	bool GetIsAlive() { return bIsAlive; }
	UFUNCTION(BlueprintNativeEvent)
	void OnDeath(AActor* Instigator);
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxHealth = 100;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
private:
	float CurHealth;
	bool bIsAlive = true;
};
