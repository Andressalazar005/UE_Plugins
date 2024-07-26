// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interfaces/GOAPGoal.h"
#include "GoapBaseGoal.generated.h"

/**
 * 
 */
UCLASS()
class TFS_GOAP_API UGoapBaseGoal : public UObject, public IGOAPGoal
{
	GENERATED_BODY()
public:


	// Inherited via IGOAPGoal
	virtual bool IsGoalComplete() const override;

	virtual void Activate() override;

	virtual void Terminate() override;

};
