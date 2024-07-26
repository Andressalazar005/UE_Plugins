// Fill out your copyright notice in the Description page of Project Settings.


#include "TFS_GOAP_Planner.h"

TArray<UTFS_GOAP_Action*> UTFS_GOAP_Planner::Plan(TArray<TSubclassOf<UTFS_GOAP_Action>> AvailableActions, UTFS_WorldState* StartState, UTFS_WorldState* GoalState)
{
    TArray<UTFS_GOAP_Action*> ParsedActions;
    for (auto Action : AvailableActions)
    {
        ParsedActions.Add(Cast<UTFS_GOAP_Action>(Action));
    }

    UTFS_WorldState* CurrentState = CreateNewState(StartState->Preconditions); // Initialize the StartState
    CurrentState = StartState; // Copy the content from StartState
    UTFS_WorldState* CurrentGoalState = CreateNewState(GoalState->Preconditions); // Initialize the GoalState
   CurrentGoalState = GoalState; // Copy the content from GoalState

    TQueue<Node> OpenSet;
    TMap<uint32, Node> Visited;

    Node StartNode;
    StartNode.State = CurrentState;
    StartNode.Cost = 0;
    StartNode.Heuristic = CalculateHeuristic(CurrentState, CurrentGoalState);
    OpenSet.Enqueue(StartNode);

    while (!OpenSet.IsEmpty()) {
        Node CurrentNode;
        OpenSet.Dequeue(CurrentNode);

        if (GoalReached(CurrentNode.State, CurrentGoalState)) {
            return CurrentNode.Actions;
        }

        Visited.Add(HashState(CurrentNode.State), CurrentNode);

        for (UTFS_GOAP_Action* Action : ParsedActions) {
            UTFS_WorldState* NewState = CurrentNode.State;
            if (Action->CheckPreconditions(NewState)) {
                Action->ApplyEffects(NewState);
                float NewCost = CurrentNode.Cost + Action->ActionCost;
                float Heuristic = CalculateHeuristic(NewState, CurrentGoalState);
                Node Successor;
                Successor.State = NewState;
                Successor.Cost = NewCost;
                Successor.Heuristic = Heuristic;
                Successor.Actions = CurrentNode.Actions;
                Successor.Actions.Add(Action);

                uint32 Hash = HashState(NewState);
                Node* VisitedNode = Visited.Find(Hash);
                if (!VisitedNode || NewCost < VisitedNode->Cost) {
                    OpenSet.Enqueue(Successor);
                }
            }
        }
    }

    // Clean up dynamic memory
    if (CurrentState != nullptr)
    {
        CurrentState->ConditionalBeginDestroy();
    }
    if (CurrentGoalState != nullptr)
    {
        CurrentGoalState->ConditionalBeginDestroy();
    }

    return TArray<UTFS_GOAP_Action*>();
}

float UTFS_GOAP_Planner::GetTotalCost(const Node& node) const
{
    return node.Cost + node.Heuristic;
}

bool UTFS_GOAP_Planner::GoalReached(UTFS_WorldState* currentState, UTFS_WorldState* goalState) const
{
    auto currentStatePreconditions = currentState->Preconditions;
    auto goalStatePreconditions = goalState->Preconditions;

    // Check if the number of precondition pairs in currentState and goalState match
    if (currentStatePreconditions.Num() != goalStatePreconditions.Num()) {
        return false; // Different number of precondition pairs, goals not reached
    }

    // Compare each pair of strings and bools in the precondition arrays
    for (int32 i = 0; i < currentStatePreconditions.Num(); ++i) {
        auto currentPair = currentStatePreconditions[i];
        auto goalPair = goalStatePreconditions[i];

        // Check if the strings match and the bool values match
        if (currentPair.Key == goalPair.Key && currentPair.Value == goalPair.Value) {
            continue; // This pair matches, continue to the next pair
        }
        else {
            return false; // Found a pair that doesn't match, goals not reached
        }
    }

    return true; // All pairs match, goals reached
}

uint32 UTFS_GOAP_Planner::HashState(UTFS_WorldState* state) const
{
    return FCrc::MemCrc_DEPRECATED(&state, sizeof(UTFS_WorldState));
}

float UTFS_GOAP_Planner::CalculateHeuristic(UTFS_WorldState* currentState, UTFS_WorldState* goalState) const
{
    auto currentStatePreconditions = currentState->Preconditions;
    auto goalStatePreconditions = goalState->Preconditions;

    float mismatchCount = 0.0f;
    float squaredDistance = 0.0f;

    // Check if the number of precondition pairs in currentState and goalState match
    int32 numPairs = FMath::Min(currentStatePreconditions.Num(), goalStatePreconditions.Num());

    // Compare each pair of precondition strings and bool values
    for (int32 i = 0; i < numPairs; ++i) {
        auto currentPair = currentStatePreconditions[i];
        auto goalPair = goalStatePreconditions[i];

        // Check if the strings match and the bool values mismatch
        if (currentPair.Key == goalPair.Key && currentPair.Value != goalPair.Value) {
            mismatchCount += 1.0f; // Increase count for each mismatched pair
            squaredDistance += 1.0f; // Increase squared distance for each mismatched pair
        }
    }

    // Use a weighted sum of count and distance as the heuristic value
    // You can adjust the weights (alpha and beta) based on your domain knowledge
    float alpha = 1.0f; // Weight for mismatch count
    float beta = 1.0f; // Weight for squared distance
    float heuristicValue = alpha * mismatchCount + beta * FMath::Sqrt(squaredDistance);

    return heuristicValue; // Return the combined heuristic value
}

UTFS_WorldState* UTFS_GOAP_Planner::CreateNewState(TArray<FPreconPair>& Conditions)
{
    UTFS_WorldState* NewState = NewObject<UTFS_WorldState>();

    // Assign FPreconPair instances to the UTFS_WorldState's Preconditions array
    for (const FPreconPair& Pair : Conditions)
    {
        NewState->Preconditions.Add(Pair);
    }

    return NewState;
}