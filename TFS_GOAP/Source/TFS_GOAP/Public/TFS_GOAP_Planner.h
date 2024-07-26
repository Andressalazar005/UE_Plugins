// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <TFS_WorldState.h>
#include <TFS_GOAP_Action.h>
#include "TFS_GOAP_Planner.generated.h"

/**
 * 
 */
UCLASS()
class TFS_GOAP_API UTFS_GOAP_Planner : public UObject
{
	GENERATED_BODY()


public:
	TArray<UTFS_GOAP_Action*> Plan(TArray<TSubclassOf<UTFS_GOAP_Action>> AvailableActions, UTFS_WorldState* StartState,UTFS_WorldState* GoalState);

private:
	struct Node
	{
		UTFS_WorldState* State;
		float Cost;
		float Heuristic;
		TArray<UTFS_GOAP_Action*> Actions;
	};

	float GetTotalCost(const Node& node) const;
	bool GoalReached(UTFS_WorldState* currentState, UTFS_WorldState* goalState) const;
	uint32 HashState(UTFS_WorldState* state) const;
	float CalculateHeuristic(UTFS_WorldState* currentState, UTFS_WorldState* goalState) const;

	UTFS_WorldState* CreateNewState(TArray<FPreconPair>& Conditions);

	
	


};
