// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DebugSystemData.h"
#include "DebugSystem.generated.h"

#define DEBUG_ID_OFFSET 500

struct FHitboxShape;
enum class EHitboxShapes : uint8;

DECLARE_LOG_CATEGORY_EXTERN(RetronLog, Display, All);

/*not-greenish yellow*/
#define TronYellow FColor(255, 235, 0)

#define TronFATAL(msg) UDebugSystem::LogFatal("msg");

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class LOGGER_API UDebugSystem : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDebugSystemData* LocalData;

	UDebugSystem();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	static void Log(FString Message, EDebugCategory Category, float Duration = 3.5f, int IdOffset = 0, bool ShowOnGameWindow = true);

	static void LogWarning(FString Message, EDebugCategory Category, float Duration = 6.f, int IdOffset = 0, bool ShowOnGameWindow = true);

	static void LogError(FString Message, EDebugCategory Category, float Duration = 10.f, int IdOffset = -DEBUG_ID_OFFSET - 1, bool ShowOnGameWindow = true);

	static void LogFatal(FString Message);

	UFUNCTION(BlueprintPure)
	static bool IsDebugCategoryEnabled(EDebugCategory Category);

	static UDebugSystemData* Data;

	void RefreshLocalData();

private:
	static void LogInternal(FString Message, EDebugCategory Category, EErrorLevels ErrorLevel, float Duration, int IdOffset, bool ShowOnGameWindow, FColor Color);
	static bool IsErrorOrFatal(EErrorLevels ErrorLevel);

};
