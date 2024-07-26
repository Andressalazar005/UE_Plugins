// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "NiagaraSystem.h"
#include "Chaos/ChaosEngineInterface.h"
#include "WeaponReactionComponents.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class IMPACTRECTIONS_API UWeaponReactionComponents : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponReactionComponents();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	// VFX Particles
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reaction VFX")
	TMap<TEnumAsByte<EPhysicalSurface>, UNiagaraSystem*> ParticleReactionMap;
	//Decals
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reaction VFX | Decals")
	float DecalFadeDistance = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reaction VFX | Decals")
	float DecalUniformScaleMin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reaction VFX | Decals")
	float DecalUniformScaleMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reaction VFX | Decals")
	float DecalLiftime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reaction VFX | Decals")
	TMap<TEnumAsByte<EPhysicalSurface>, UMaterialInterface*> DecalReactionMap;
	

	//
	UFUNCTION(BlueprintCallable)
	void OnHit(FVector Location,FRotator Rotation, EPhysicalSurface SurfaceType, float StrengthMultiplier);

	UFUNCTION(BlueprintPure)
	void FindSpawnInverseRotation(FRotator& Rotation);
};
