// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/AudioComponent.h"
#include <ConstantQNRT.h>
#include "AudioPlayer.generated.h"

UCLASS(Blueprintable,BlueprintType)
class AUDIOMANAGER_API AAudioPlayer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAudioPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UAudioComponent* AudioPlayer;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<float> SpectrumAnalysis;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CurrentTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Default|Audio Analasys")
	UConstantQNRT* CurrentCachedAnalyzer;



};
