// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioPlayer.h"

// Sets default values
AAudioPlayer::AAudioPlayer()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	AudioPlayer = CreateDefaultSubobject<UAudioComponent>("MusciPlayer");
}

// Called when the game starts or when spawned
void AAudioPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAudioPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

