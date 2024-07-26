// Fill out your copyright notice in the Description page of Project Settings.

#include "AI_Brain.h"

UAI_Brain::UAI_Brain()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAI_Brain::BeginPlay()
{
	Super::BeginPlay();
}

void UAI_Brain::Initialize(AAIController* OwningController)
{
	Controller = OwningController;
	Planner = NewObject<UTFS_GOAP_Planner>();
	// Other initialization code
}

void UAI_Brain::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// Update logic
}

void UAI_Brain::DefineActions()
{
	// Define actions
}

void UAI_Brain::PlanAndExecute()
{
	if (!CurrentState || !GoalState) {
		// Handle null states
		return;
	}

	TArray<UTFS_GOAP_Action*> Plan = Planner->Plan(Actions, CurrentState, GoalState);

	for (UTFS_GOAP_Action* Action : Plan) {
		if (Action->CheckPreconditions(CurrentState)) {
			Action->ApplyEffects(CurrentState);
			Action->PerformAction();
		}
	}
}

void UAI_Brain::DefineGoals()
{
	for (TSubclassOf<UGoapBaseGoal>& GoalClass : Goals)
	{
		UGoapBaseGoal* GoalInstance = NewObject<UGoapBaseGoal>(this, GoalClass);
		// Optionally perform additional setup
	}
}

void UAI_Brain::SetGoal(UGoapBaseGoal* NewGoal)
{
	// Logic to set the current goal of the AI
	//GoalState = Planner.w; ...; // Set the GoalState based on the new goal's conditions
	// NewGoal->Activate(); // Activate the new goal
}

UGoapBaseGoal* UAI_Brain::DetermineNextGoal()
{
	UGoapBaseGoal* NewGoal = NewObject<UGoapBaseGoal>();
	return NewGoal != nullptr ? NewGoal : nullptr;
}

void UAI_Brain::ProcessNextGoal()
{
	UGoapBaseGoal* NextGoal = DetermineNextGoal();
	if (NextGoal)
	{
		IGOAPGoal* InterfaceGoal = Cast<IGOAPGoal>(NextGoal);
		if (InterfaceGoal)
		{
			// You can call IGOAPGoal functions using InterfaceGoal here
			InterfaceGoal->IsGoalComplete();
			InterfaceGoal->Activate();
			InterfaceGoal->Terminate();
		}
	}
}

