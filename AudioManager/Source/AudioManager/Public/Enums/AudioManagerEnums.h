// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AudioManagerEnums.generated.h"
/**
 * 
 */
UENUM(BlueprintType)
enum class EAudioState:uint8
{
    AS_Boss        UMETA(DisplayName = "Boss"),
    AS_Interior    UMETA(DisplayName = "Interior"),
    AS_Exterior    UMETA(DisplayName = "Exterior"),
    AS_Calm        UMETA(DisplayName = "Calm"),
    AS_Combat      UMETA(DisplayName = "Combat")
};

