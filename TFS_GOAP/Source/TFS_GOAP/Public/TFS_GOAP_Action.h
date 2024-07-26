// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include <TFS_WorldState.h>
#include "TFS_GOAP_Action.generated.h"

/**
 * 
 */
UCLASS(Abstract,BlueprintType, Blueprintable)
class TFS_GOAP_API UTFS_GOAP_Action : public UObject, public FTickableGameObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ActionCost = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	UTFS_WorldState* SuccessPreconditions;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,Instanced)
	UTFS_WorldState* Effects;

	UFUNCTION(BlueprintCallable)
	bool CheckPreconditions(const UTFS_WorldState* CurrentState);
	UFUNCTION(BlueprintCallable)
	void ApplyEffects(UTFS_WorldState* CurrentState) const;
	UFUNCTION(BlueprintNativeEvent)
	void PerformAction();


protected:

private:


	// Inherited via FTickableGameObject
	virtual void Tick(float DeltaTime) override;

	virtual TStatId GetStatId() const override;

};
