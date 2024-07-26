// Fill out your copyright notice in the Description page of Project Settings.


#include "AI_Director.h"

// Sets default values
AAI_Director::AAI_Director()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAI_Director::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAI_Director::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

//bool UGOAP_WorldState::IsStateSatisfied(const UGOAP_WorldState& _goalState)
//{
//	for (const auto& goal : _goalState.Properties)
//	{
//		bool bIsFound = false;
//		for (const auto& property : Properties)
//		{
//			if (goal.Key == property.Key && goal.Value == property.Value)
//			{
//				bIsFound = true;
//				break;
//			}
//			if (!bIsFound)
//			{
//				return false;
//			}
//
//		}
//		return true;
//	}
//}
//
//void UGOAP_WorldState::Tick(float DeltaTime)
//{
//}
//
//TStatId UGOAP_WorldState::GetStatId() const
//{
//	return TStatId();
//}

