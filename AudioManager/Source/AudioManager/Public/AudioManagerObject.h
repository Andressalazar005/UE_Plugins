// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Enums/AudioManagerEnums.h"
#include "Structs/AudioStructs.h"
#include "Templates/Tuple.h"
#include "Containers/Map.h"
#include "Components/AudioComponent.h"
#include "AudioPlayer.h"
#include "LoudnessNRT.h"
#include <ConstantQNRT.h>
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "AudioManagerObject.generated.h"


UCLASS(BlueprintType, Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AUDIOMANAGER_API UAudioManagerObject : public UObject , public FTickableGameObject
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAudioManagerObject();
	~UAudioManagerObject();

protected:


public:	

	UGameInstance* GameInstance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AAudioPlayer> AudioPlayerClass;
	UPROPERTY(EditAnywhere, BLueprintReadWrite)
	AAudioPlayer* AudioSourceActor;
	UPROPERTY(EditAnywhere, BLueprintReadWrite)
	UAudioComponent* AudioSource;
	//variables 

	UPROPERTY(EditAnywhere, BLueprintReadWrite)
	UDataTable* TrackTable;
	UPROPERTY(EditAnywhere, BLueprintReadWrite)
	TArray<USoundBase*> AudioTracks;
	UPROPERTY(EditAnywhere, BLueprintReadWrite)
	TMap<FName, EAudioState> FallbackMap;
	UPROPERTY()
	UAudioManagerObject* Instance;

	UPROPERTY(EditAnywhere, BLueprintReadWrite)
	EAudioState CurrentAudioState;
	EAudioState ChachedLevelState;

	TArray<TTuple<UObject*,FOverrides>> OverrideStack;
	UFUNCTION()
	void Initialize();
	UFUNCTION()
	void OnLoadComplete(FName LevelName);
	UFUNCTION()
	void CreateAudioSource();

	UFUNCTION(BlueprintPure)
	UAudioManagerObject* GetAudioManager() { return Instance; }

	UFUNCTION(BlueprintCallable)
	virtual void Pause();
	UFUNCTION(BlueprintCallable)
	virtual void Play();
	UFUNCTION(BlueprintCallable)
	virtual void Stop();
	UFUNCTION(BlueprintCallable)
	void Mute();
	bool bIsMuted = false;
	UFUNCTION(BlueprintCallable)
	void OverrideCurrentState(EAudioState NewState);

	UFUNCTION(BlueprintCallable)
	void AddToOverrideStack(UObject* Key, FOverrides  Pair);
	void AddToOverrideStackInternal(TPair<UObject*, FOverrides> Override);
	UFUNCTION(BlueprintCallable)
	void RemoveFromOverrideStack(UObject * Key);
	
	void HandleOverrideStackChange();
	UFUNCTION(BlueprintCallable)
	void FadeIn();
	UFUNCTION(BlueprintCallable)
	void FadeOut();

	UFUNCTION(BlueprintCallable)
	void DuckingStart();
	UFUNCTION(BlueprintCallable)
	void DuckingEnd();
	
	UFUNCTION(BlueprintCallable)
	void PlaySound2D(USoundBase* SoundToPlay);

	UFUNCTION(BlueprintCallable)
	void PlaySoundAtLocations(FVector Location, USoundBase* Sound);
	//UFUNCTION(BlueprintCallable)
	// Inherited via FTickableGameObject
	virtual void Tick(float DeltaTime) override;


	virtual TStatId GetStatId() const override;


	UFUNCTION(BlueprintCallable)
	TArray<USoundBase*> GetTracksFromRow(EAudioState State);

	UFUNCTION(BlueprintCallable)
	EAudioState FindFallbackStateOnLoad(FName LevelName);

	UFUNCTION()
	void OnAudioEnded(EAudioComponentPlayState NewState);
	UFUNCTION()
	void OnAudioFinished();

	void PlayNextTrack();




	//Spectrum Analasys for visualizer 

	UPROPERTY(EditAnywhere, BlueprintReadWrite,category = "Default|Audio Analasys")
	UConstantQNRT* CurrentCachedAnalyzer;
	UPROPERTY(EditAnywhere, BLueprintReadWrite)
	UMaterialParameterCollection* VisualizerMaterialParameter;
	/*UPROPERTY(EditAnywhere, BLueprintReadWrite)*/
	UMaterialParameterCollectionInstance* VisualizerMaterialParameterInstance;
	TArray<float> AnalyzerData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Default|Audio Analasys")
	TMap<USoundBase*, UConstantQNRT*> AnalyzerMap;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Default|Audio Analasys")
	int32 ChannelStart =4;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Default|Audio Analasys")
		bool bAverageChannels;
		UPROPERTY(EditAnywhere, BlueprintReadWrite, category = "Default|Audio Analasys")
	int32 ChannelEnd = 15;
	/*UFUNCTION()*/
	UConstantQNRT* FindAnalyzerFromMap(USoundBase* CurSound);
	/*UFUNCTION()*/
	void AnalyzeSpectrumData(float DeltaTime);
	UFUNCTION()
	void UpdateParamenterCollection(TArray<float> values);
	float CurrentTime;
	//

};
