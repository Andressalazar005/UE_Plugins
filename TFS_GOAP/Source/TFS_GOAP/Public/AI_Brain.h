// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GoapBaseGoal.h"
#include "TFS_GOAP_Action.h"
#include "TFS_WorldState.h"
#include "TFS_GOAP_Planner.h"
#include <AIController.h>
#include "Interfaces/GOAPGoal.h"
#include "AI_Brain.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TFS_GOAP_API UAI_Brain : public UActorComponent
{
	GENERATED_BODY()

public:
	UAI_Brain();

protected:
	virtual void BeginPlay() override;

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GOAP")
	TArray<TSubclassOf<UTFS_GOAP_Action>> Actions;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GOAP")
	TArray<TSubclassOf<UGoapBaseGoal>> Goals;
	
	
	void Initialize(AAIController* OwningController);
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void DefineActions();

	UFUNCTION(BlueprintCallable)
		void PlanAndExecute();

	UFUNCTION(BlueprintCallable)
		void DefineGoals();

	UFUNCTION(BlueprintCallable)
		void SetGoal(UGoapBaseGoal* NewGoal);

	UFUNCTION(BlueprintCallable)
	UGoapBaseGoal* DetermineNextGoal();
	

	void ProcessNextGoal();

private:
	AAIController* Controller;
	UTFS_WorldState* CurrentState;
	UTFS_WorldState* GoalState;
	UTFS_GOAP_Planner* Planner;

};