// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Containers/Map.h"
#include "Templates/Tuple.h"
#include <GOAP_Enums.h>
#include "TFS_WorldState.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct FPreconPair
{
    GENERATED_BODY()


    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (GetOptions = "Options"));
    FString Key;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ForceInlineRow))
    bool Value;

    
    // Constructor to initialize values
    FPreconPair()
        : Key(""), Value(false)
    {
    }

    // Convenience constructor
    FPreconPair(const FString& InKey, bool InValue)
        : Key(InKey), Value(InValue)
    {
    }

    bool operator==(const FPreconPair& Other) const
    {
        return Key == Other.Key && Value == Other.Value;
    }
    
    
};

UCLASS(BlueprintType,Blueprintable,EditInlineNew)
class TFS_GOAP_API UTFS_WorldState : public UObject, public FTickableGameObject
{
	GENERATED_BODY()
	

public:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<FPreconPair> Preconditions;

	// Inherited via FTickableGameObject
	virtual void Tick(float DeltaTime) override;

	virtual TStatId GetStatId() const override;


	// Functions to manipulate the state
    UFUNCTION()
    void AddPrecondition(const FString& Key, bool Value);
    UFUNCTION()
    void RemovePrecondition(const FString& Key);
    UFUNCTION()
    bool GetPreconditionValue(const FString& Key) const;
    
 

    UFUNCTION()
    inline TArray<FString> Options() {
        TArray<FString> DisplayNames;
        UEnum* EnumPTR = FindObject<UEnum>(ANY_PACKAGE, TEXT("EGOAP_Conditions"), true);
        for (int32 i = 0; i < EnumPTR->NumEnums(); ++i)
        {
            FString EnumName = EnumPTR->GetNameStringByIndex(i);
            FString DisplayName = EnumPTR->GetDisplayNameTextByIndex(i).ToString();

            // Use DisplayName in your logic or add it to an array
            if(DisplayName != "EGOAP MAX")
                DisplayNames.Add(DisplayName);
        }
        return DisplayNames;
    };
};
