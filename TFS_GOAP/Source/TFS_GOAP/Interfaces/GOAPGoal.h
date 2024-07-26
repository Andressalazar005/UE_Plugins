// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GOAPGoal.generated.h"


UINTERFACE(Blueprintable)
class TFS_GOAP_API UGOAPGoal : public UInterface
{
	GENERATED_BODY()
	
};
class TFS_GOAP_API IGOAPGoal
{
    GENERATED_BODY()

public:
    // Pure virtual functions to be implemented by classes using this interface
    virtual bool IsGoalComplete() const = 0;
    virtual void Activate() = 0;
    virtual void Terminate() = 0;
};