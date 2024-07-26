// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NiagaraSystem.h"
#include "CharacterReactionsComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CHARACTERCOMPONENTS_API UCharacterReactionsComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCharacterReactionsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* DeathMontage;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* GetUpFrontAnim;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* GetBackFrontAnim;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* HitReactionAudio;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* AlertReactionAudio;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* OnHitCalloutReactionAudio;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UNiagaraSystem* HitEffect;
		
};
