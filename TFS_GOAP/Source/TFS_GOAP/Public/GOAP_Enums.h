// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class EGOAP_Conditions :uint8
{
    IsUnderAttack UMETA(DisplayName = "IsUnderAttack"),
    HasWeapon UMETA(DisplayName = "Has Weapon"),
    HasAmmo UMETA(DisplayName = "Has Ammo"),
    IsHungry UMETA(DisplayName = "Is Hungry"),
    IsTired UMETA(DisplayName = "Is Tired"),
    IsHealthy UMETA(DisplayName = "Is Healthy"),
    HasKey UMETA(DisplayName = "Has Key"),
    IsInCombat UMETA(DisplayName = "Is In Combat"),
    HasQuestItem UMETA(DisplayName = "Has Quest Item"),
    IsInStealth UMETA(DisplayName = "Is In Stealth"),
    IsInGroup UMETA(DisplayName = "Is In Group"),
    IsInjured UMETA(DisplayName = "Is Injured"),
    IsWarm UMETA(DisplayName = "Is Warm"),
    IsCold UMETA(DisplayName = "Is Cold"),
    IsWet UMETA(DisplayName = "Is Wet"),
    IsThirsty UMETA(DisplayName = "Is Thirsty"),
    HasMap UMETA(DisplayName = "Has Map"),
    IsVisible UMETA(DisplayName = "Is Visible"),
    IsHidden UMETA(DisplayName = "Is Hidden"),
    HasMoney UMETA(DisplayName = "Has Money"),
    IsAggressive UMETA(DisplayName = "Is Aggressive"),
    IsCalm UMETA(DisplayName = "Is Calm"),
    IsFocused UMETA(DisplayName = "Is Focused"),
    IsDistracted UMETA(DisplayName = "Is Distracted"),
    IsFriendly UMETA(DisplayName = "Is Friendly"),
    IsHostile UMETA(DisplayName = "Is Hostile"),
    IsAlert UMETA(DisplayName = "Is Alert"),
    IsRelaxed UMETA(DisplayName = "Is Relaxed"),
    IsConfused UMETA(DisplayName = "Is Confused"),
    IsCurious UMETA(DisplayName = "Is Curious"),
    IsSmart UMETA(DisplayName = "Is Smart"),
    IsClumsy UMETA(DisplayName = "Is Clumsy"),
    IsSkilled UMETA(DisplayName = "Is Skilled"),
    IsExperienced UMETA(DisplayName = "Is Experienced"),
    IsNovice UMETA(DisplayName = "Is Novice"),
    IsQuick UMETA(DisplayName = "Is Quick"),
    EGOAP_MAX UMETA(Hidden),
};
