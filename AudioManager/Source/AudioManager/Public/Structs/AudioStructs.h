// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enums/AudioManagerEnums.h"
#include "AudioStructs.generated.h"

USTRUCT(BlueprintType)
struct FOverrides
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    EAudioState AudioState;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    USoundBase* OverrideSound;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    bool bCanDuck = false;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    bool bShouldFade = false;
};

USTRUCT(BlueprintType)
struct FLevelFallbacks:public FTableRowBase
{
    GENERATED_BODY()
public:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    TEnumAsByte<EAudioState> AudioStateFallback;

};
USTRUCT(BlueprintType)
struct FAudioTracks :public FTableRowBase
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    TArray<USoundBase*> SoundTracks;
};

