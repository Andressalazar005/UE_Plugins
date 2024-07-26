// Fill out your copyright notice in the Description page of Project Settings.


#include "TFS_GOAP_Action.h"

bool UTFS_GOAP_Action::CheckPreconditions(const UTFS_WorldState* CurrentState)
{
	for (auto Success : SuccessPreconditions->Preconditions)
	{

		for (auto Property : CurrentState->Preconditions)
		{
			if (Success.Key == Property.Key)
			{
				if (Success.Value != Property.Value)
				{
					return false;
				}
			}
		}
	}
	return true;
}

void UTFS_GOAP_Action::ApplyEffects(UTFS_WorldState* CurrentState) const
{
	
	
	for (auto effectprecondition : Effects->Preconditions)
	{
		for (auto stateprecondition : CurrentState->Preconditions)
		{
			if (effectprecondition.Key == stateprecondition.Key)
			{
				if (effectprecondition.Value != stateprecondition.Value)
				{
					stateprecondition.Value = effectprecondition.Value;
				}
			}
			else if (!CurrentState->Preconditions.Contains(effectprecondition))
			{
				CurrentState->AddPrecondition(effectprecondition.Key,effectprecondition.Value);
			}
		}
	}
		
	
}

void UTFS_GOAP_Action::PerformAction_Implementation()
{

}

void UTFS_GOAP_Action::Tick(float DeltaTime)
{
}

TStatId UTFS_GOAP_Action::GetStatId() const
{
	return TStatId();
}
