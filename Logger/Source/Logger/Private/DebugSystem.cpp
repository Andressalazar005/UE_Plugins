// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugSystem.h"
#include "Kismet/KismetSystemLibrary.h"


static constexpr int32 SPHERE_SEGMENTS = 12;
static constexpr int32 CONE_SEGMENTS = 16;
static constexpr int32 RING_SEGMENTS = 20;

DEFINE_LOG_CATEGORY(RetronLog);

UDebugSystemData* UDebugSystem::Data = nullptr;

UDebugSystem::UDebugSystem()
{
}

void UDebugSystem::BeginPlay()
{
	Super::BeginPlay();
	RefreshLocalData();
}

void UDebugSystem::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UDebugSystem::Data = nullptr;
}

void UDebugSystem::Log(FString Message, EDebugCategory Category, float Duration, int IdOffset, bool ShowOnGameWindow)
{
	LogInternal(Message, Category, EErrorLevels::TEL_Display, Duration, IdOffset, ShowOnGameWindow, FColor::Silver);
}

void UDebugSystem::LogWarning(FString Message, EDebugCategory Category, float Duration, int IdOffset, bool ShowOnGameWindow)
{
	LogInternal(Message, Category, EErrorLevels::TEL_Warning, Duration, IdOffset, ShowOnGameWindow, TronYellow);
}

void UDebugSystem::LogError(FString Message, EDebugCategory Category, float Duration, int IdOffset, bool ShowOnGameWindow)
{
	LogInternal(Message, Category, EErrorLevels::TEL_Error, Duration, IdOffset, ShowOnGameWindow, FColor::Red);
}

void UDebugSystem::LogFatal(FString Message)
{
	LogInternal(Message, EDebugCategory::DC_AlwaysShown, EErrorLevels::TEL_Fatal, true, 0, 1.f, FColor::Red);
}

void UDebugSystem::RefreshLocalData()
{
	UDebugSystem::Data = LocalData;
}

void UDebugSystem::LogInternal(FString Message, EDebugCategory Category, EErrorLevels ErrorLevel, float Duration, int IdOffset, bool ShowOnGameWindow, FColor Color)
{
	if (IsErrorOrFatal(ErrorLevel) || IsDebugCategoryEnabled(Category))
	{
		//appends category before message
		Message = UEnum::GetDisplayValueAsText(Category).ToString() + ": " + Message;

		switch (ErrorLevel)
		{
		case EErrorLevels::TEL_Display:
			UE_LOG(RetronLog, Display, TEXT("%s"), *Message);
			break;

		case EErrorLevels::TEL_Warning:
			UE_LOG(RetronLog, Warning, TEXT("%s"), *Message);
			break;

		case EErrorLevels::TEL_Error:
			UE_LOG(RetronLog, Error, TEXT("%s"), *Message);
			break;

		case EErrorLevels::TEL_Fatal:
			UE_LOG(RetronLog, Fatal, TEXT("%s"), *Message);
			break;

		default:
			UE_LOG(RetronLog, Display, TEXT("%s"), *Message);
			break;
		}

		if (ShowOnGameWindow && GEngine)
		{
			GEngine->AddOnScreenDebugMessage(DEBUG_ID_OFFSET + IdOffset, Duration, Color, *Message);
		}
	}
}

bool UDebugSystem::IsErrorOrFatal(EErrorLevels ErrorLevel)
{
	return ErrorLevel == EErrorLevels::TEL_Error || ErrorLevel == EErrorLevels::TEL_Fatal;
}

bool UDebugSystem::IsDebugCategoryEnabled(EDebugCategory Category)
{
	if (!UDebugSystem::Data || Category == EDebugCategory::DC_AlwaysShown)
	{
		return true;
	}

	const bool bIsEnabled = IsValid(UDebugSystem::Data) &&
		UDebugSystem::Data->DebugCategoryMap.Contains(Category) &&
		UDebugSystem::Data->DebugCategoryMap[Category] == true;

	return bIsEnabled;
}

