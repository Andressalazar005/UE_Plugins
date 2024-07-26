// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DebugSystemData.generated.h"

UENUM(BlueprintType)
enum class EDebugCategory : uint8
{
	DC_AlwaysShown 			UMETA(DisplayName = "Uncategorized"),

	DC_Camera				UMETA(DisplayName = "Camera"),
	DC_ActionOverrides		UMETA(DisplayName = "Action Overrides"),
	DC_Animations			UMETA(DisplayName = "Animations"),
	DC_Audio				UMETA(DisplayName = "Audio"),
	DC_Attack				UMETA(DisplayName = "Attacks"),
	DC_Input				UMETA(DisplayName = "Input"),
	DC_Movement				UMETA(DisplayName = "Movement"),
	DC_Dialogue				UMETA(DisplayName = "Dialogue"),
	DC_Interaction			UMETA(DisplayName = "Interaction"),
	DC_Messaging			UMETA(DisplayName = "Messaging API"),
	DC_Targeting			UMETA(DisplayName = "Targeting"),
	DC_LifeCycle			UMETA(DisplayName = "Life Cycle"),
	DC_AI_Raw				UMETA(DisplayName = "AI Raw"),
	DC_AI_Enemy				UMETA(DisplayName = "AI Enemy"),
	DC_AI_Movement			UMETA(DisplayName = "AI Movement"),
	DC_Cheats				UMETA(DisplayName = "Cheats"),
	DC_LevelStreaming		UMETA(DisplayName = "Level Streaming"),
	DC_StaticMeshCollision	UMETA(DisplayName = "Static Mesh Collision"),
	DC_Navigation			UMETA(DisplayName = "Navigation System"),
	DC_UI					UMETA(DisplayName = "UI"),
	DC_Inventory			UMETA(DisplayName = "Inventory"),
	DC_SaveLoad				UMETA(DisplayName = "SaveLoad"),
	DC_TimeOfDay			UMETA(DisplayName = "TimeOfDay"),
	DC_Collision			UMETA(DisplayName = "Collision"),
	DC_Managers			UMETA(DisplayName = "Managers"),

	MAX						UMETA(Hidden)

};
ENUM_CLASS_FLAGS(EDebugCategory);
ENUM_RANGE_BY_FIRST_AND_LAST(EDebugCategory, EDebugCategory::DC_AlwaysShown, EDebugCategory::MAX);

UENUM(BlueprintType)
enum class EErrorLevels : uint8
{
	TEL_Display				UMETA(DisplayName = "Display"),
	TEL_Warning				UMETA(DisplayName = "Warning"),
	TEL_Error				UMETA(DisplayName = "Error"),
	TEL_Fatal				UMETA(DisplayName = "Fatal"),

};
UCLASS()
class LOGGER_API UDebugSystemData : public UDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(EditFixedSize, EditAnywhere, BlueprintReadWrite)
	TMap<EDebugCategory, bool> DebugCategoryMap;
	UDebugSystemData();
};
