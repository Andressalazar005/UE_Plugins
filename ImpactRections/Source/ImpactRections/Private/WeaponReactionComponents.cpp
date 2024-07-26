// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponReactionComponents.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values for this component's properties
UWeaponReactionComponents::UWeaponReactionComponents()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeaponReactionComponents::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWeaponReactionComponents::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWeaponReactionComponents::OnHit(FVector Location,  FRotator Rotation, EPhysicalSurface SurfaceType, float StrengthMultiplier)
{
	UNiagaraSystem* VFXToSpawn;
	UMaterialInterface* DecalMat;
	//Set VFX to spawn 
	VFXToSpawn = *ParticleReactionMap.Find(SurfaceType);
	DecalMat = *DecalReactionMap.Find(SurfaceType);

	//Spawn Particle Effect At Hit Location
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), VFXToSpawn, Location, Rotation);

	//Spawn Decal at hit location
	FindSpawnInverseRotation(Rotation);
	float Scale = FMath::RandRange(DecalUniformScaleMin, DecalUniformScaleMax);
	UDecalComponent* Decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DecalMat,(FVector)(Scale), Location, Rotation, DecalLiftime);
	Decal->SetFadeScreenSize(DecalFadeDistance);
}

void UWeaponReactionComponents::FindSpawnInverseRotation(FRotator& Rotation)
{
	Rotation = Rotation.GetInverse();
}

