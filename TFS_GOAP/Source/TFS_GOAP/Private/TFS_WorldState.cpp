// Fill out your copyright notice in the Description page of Project Settings.


#include "TFS_WorldState.h"

void UTFS_WorldState::Tick(float DeltaTime)
{
}

TStatId UTFS_WorldState::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(UTFS_WorldState, STATGROUP_Tickables);
}

void UTFS_WorldState::AddPrecondition(const FString& Key, bool Value)
{
    FPreconPair Pair = FPreconPair(Key,Value);
	Preconditions.Add(Pair);
}

void UTFS_WorldState::RemovePrecondition(const FString& Key)
{
    for (int32 i = Preconditions.Num() - 1; i >= 0; --i) {
        if (Preconditions[i].Key == Key) {
            Preconditions.RemoveAt(i);
            break;
        }
    }
}

bool UTFS_WorldState::GetPreconditionValue(const FString& Key) const
{
    for (auto Precondition : Preconditions) {
        if (Precondition.Key == Key) {
            return Precondition.Value;
        }
    }
    // If the precondition key doesn't exist, return a default value (false in this case)
    return false;
}


