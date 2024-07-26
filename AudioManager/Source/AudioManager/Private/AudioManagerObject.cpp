// Fill out your copyright notice in the Description page of Project Settings.


#include "AudioManagerObject.h"
#include "Engine/DataTable.h"
#include "Templates/Tuple.h"
#include "Kismet/GameplayStatics.h"
#include "Materials/MaterialParameterCollection.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include <Kismet/KismetMaterialLibrary.h>


UAudioManagerObject::UAudioManagerObject()
{

}

UAudioManagerObject::~UAudioManagerObject()
{
}



void UAudioManagerObject::Tick(float DeltaTime)
{
	if (CurrentCachedAnalyzer)
	{
		AnalyzeSpectrumData(DeltaTime);
	}
	else
	{
		if (AudioSourceActor)
		{
			CurrentCachedAnalyzer = AudioSourceActor->CurrentCachedAnalyzer;
		}
		else
		{
			AudioSourceActor = Cast<AAudioPlayer>(UGameplayStatics::GetActorOfClass(GetWorld(), AAudioPlayer::StaticClass()));
		}
	}
}

void UAudioManagerObject::Initialize()
{

	UWorld* World = (GEngine->GameViewport) ? GEngine->GameViewport->GetWorld() : GetWorld();
	
	AudioTracks = GetTracksFromRow(CurrentAudioState);
	if (!AudioSource)
	{
		CreateAudioSource();
	}
	if (!GameInstance)
	{
		GameInstance = Cast<UGameInstance>(UGameplayStatics::GetGameInstance(World));
	}
	if (AudioSource)
	{
		AudioSource->OnAudioPlayStateChanged.AddDynamic(this, &UAudioManagerObject::OnAudioEnded);
		AudioSource->OnAudioFinished.AddDynamic(this, &UAudioManagerObject::OnAudioFinished);
	}
	AudioTracks = GetTracksFromRow(CurrentAudioState);
	PlayNextTrack();
}

void UAudioManagerObject::OnLoadComplete(FName LevelName)
{
	if (!AudioSource)
	{
		CurrentAudioState = FindFallbackStateOnLoad(LevelName);
		CreateAudioSource();
		if (AudioSource)
		{
			AudioSource->Play();
		}
	}
}

void UAudioManagerObject::CreateAudioSource()
{
	if (!AudioSource)
	{
		AudioTracks = GetTracksFromRow(CurrentAudioState);
		AudioSourceActor = Cast<AAudioPlayer>(GameInstance->GetWorld()->SpawnActor(AudioPlayerClass));//NewObject<AAudioPlayer>(AudioPlayerClass);
		AudioSource = AudioSourceActor->AudioPlayer;
		AudioSource->SetSound(AudioTracks[0]);
		AudioSource->bAutoDestroy = false;
		//AudioSource->bIgnoreForFlushing = true;
		AudioSource->bIsMusic = true;
		AudioSource->Stop();
		
	}
}

void UAudioManagerObject::Pause()
{
	AudioSource->SetPaused(true);
}

void UAudioManagerObject::Play()
{
	if (AudioSource->GetPlayState() == EAudioComponentPlayState::Stopped)
	{
		AudioSource->Play();
	}
}

void UAudioManagerObject::Stop()
{
	AudioSource->Stop();
}

void UAudioManagerObject::Mute()
{
	bIsMuted = !bIsMuted;
	if (bIsMuted)
	{
		AudioSource->SetVolumeMultiplier(0);
	}
	else
	{
		AudioSource->SetVolumeMultiplier(1);
	}
}

void UAudioManagerObject::OverrideCurrentState(EAudioState NewState)
{
	CurrentAudioState = NewState;
	AudioTracks = GetTracksFromRow(CurrentAudioState);
	
	AudioSource->SetSound(AudioTracks[0]);
	Play();
	// add delegate to handle fading in and out automatically 
}

void UAudioManagerObject::AddToOverrideStack(UObject* Key, FOverrides Value)
{
	TPair<UObject*, FOverrides> StackEntry;
	StackEntry.Key = Key;
	StackEntry.Value = Value;
	AddToOverrideStackInternal(StackEntry);
}

void UAudioManagerObject::AddToOverrideStackInternal(TPair<UObject*, FOverrides> Override)
{
	OverrideStack.Add(Override);
}

void UAudioManagerObject::RemoveFromOverrideStack(UObject* Key)
{
	if (OverrideStack.IsValidIndex(0))
	{
		for (int i = 0; i < OverrideStack.Num(); i++)
		{
			if (OverrideStack[i].Key == Key)
			{
				OverrideStack.RemoveAt(i);
				HandleOverrideStackChange();
			}
		}
	}
	else
	{
		OverrideCurrentState(ChachedLevelState);
	}
}





void UAudioManagerObject::HandleOverrideStackChange()
{
	if (OverrideStack.IsValidIndex(0))
	{
		TTuple<UObject*, FOverrides> Pair = OverrideStack[OverrideStack.Num() - 1];
		OverrideCurrentState(Pair.Value.AudioState);
	}
}

void UAudioManagerObject::FadeIn()
{
	AudioSource->FadeIn(.3f, .1f, 0);
}

void UAudioManagerObject::FadeOut()
{
	AudioSource->FadeOut(.3f, 1);
}

void UAudioManagerObject::DuckingStart()
{
	AudioSource->AdjustVolume(0, .1f);
}

void UAudioManagerObject::DuckingEnd()
{
	AudioSource->AdjustVolume(0, 1);
}

void UAudioManagerObject::PlaySound2D(USoundBase* SoundToPlay)
{
	UGameplayStatics::PlaySound2D(GameInstance->GetWorld(), SoundToPlay);
}

void UAudioManagerObject::PlaySoundAtLocations(FVector Location, USoundBase* Sound)
{
	UGameplayStatics::PlaySoundAtLocation(GameInstance->GetWorld(), Sound, Location);
}

TStatId UAudioManagerObject::GetStatId() const
{
	return TStatId();
}

TArray<USoundBase*> UAudioManagerObject::GetTracksFromRow(EAudioState State)
{
	UE_LOG(LogTemp, Display, TEXT("Looking For tracks from table..."))
	FAudioTracks* TrackListData;
	FName TempName = UEnum::GetValueAsName(State);
	if (TrackTable)
	{
		TrackListData = TrackTable->FindRow<FAudioTracks>(TempName, "");
		UE_LOG(LogTemp, Display, TEXT("Row found! Adding tracks to array"))
		return TrackListData->SoundTracks;
	}
	if (!TrackTable)
	{
		UE_LOG(LogTemp,Display,TEXT("Track Data table Missing???"))
	}
	return TArray<USoundBase*>();
}

EAudioState UAudioManagerObject::FindFallbackStateOnLoad(FName LevelName)
{
	UE_LOG(LogTemp, Display, TEXT("Looking for fallback state after level load"))
	EAudioState State;
	if (FallbackMap.Find(LevelName))
	{
		State = *FallbackMap.Find(LevelName);
	}
	else
	{
		State = EAudioState::AS_Calm;
	}
//	VisualizerMaterialParameterInstance = GetWorld()->GetParameterCollectionInstance(VisualizerMaterialParameter);
	return State;
}

void UAudioManagerObject::OnAudioEnded(EAudioComponentPlayState NewState)
{
	UE_LOG(LogTemp, Display, TEXT("Song Ended Delegate called"))
	if (NewState == EAudioComponentPlayState::Stopped)
	{
		PlayNextTrack();
	}
}

void UAudioManagerObject::OnAudioFinished()
{
	PlayNextTrack();
	UE_LOG(LogTemp, Display, TEXT("Audio Finished, Calling PlayNextTrack"))
}

void UAudioManagerObject::PlayNextTrack()
{
	UE_LOG(LogTemp, Display, TEXT("Playing Next Track"))
	if (AudioTracks.IsValidIndex(0))
	{
		if (AudioTracks.IndexOfByKey(AudioSource->GetSound()) + 1 < AudioTracks.Num())
		{
			AudioSource->SetSound(AudioTracks[AudioTracks.IndexOfByKey(AudioSource->GetSound()) + 1]);
		}
		else
		{
			AudioSource->SetSound(AudioTracks[0]);

		}
		//LoudnessAnalyzer->Sound = Cast<USoundWave>(AudioSource->GetSound());
		CurrentCachedAnalyzer = FindAnalyzerFromMap(AudioSource->GetSound());
		CurrentTime = 0;
		AudioSourceActor->CurrentCachedAnalyzer = CurrentCachedAnalyzer;
		AudioSource->Play();
	}
	
}


UConstantQNRT* UAudioManagerObject::FindAnalyzerFromMap(USoundBase* CurSound)
{
	return *AnalyzerMap.Find(CurSound);
}

void UAudioManagerObject::AnalyzeSpectrumData(float DeltaTime)
{
	TArray<float> SpectrumAnalysis;
	 CurrentTime = UKismetSystemLibrary::GetGameTimeInSeconds(AudioSource->GetWorld());
	float AudioLength = AudioSource->GetSound()->GetDuration();
	float Modulous = FMath::Fmod(CurrentTime, AudioLength) - .1f;
	float AveragedValue;
	AnalyzerData.Empty();
	if (CurrentCachedAnalyzer)
	{
		CurrentCachedAnalyzer->GetNormalizedChannelConstantQAtTime(Modulous, 0, SpectrumAnalysis);
	}
	if (!bAverageChannels)
	{
		for (int i = ChannelStart; i < ChannelEnd; i++)
		{
			if (SpectrumAnalysis.IsValidIndex(i))
			{
				//UE_LOG(LogTemp, Display, TEXT("Current Channel Value: " + FString::SanitizeFloat(SpectrumAnalysis[i])))
				AnalyzerData.Add(SpectrumAnalysis[i]);
			}
		}
	}
	else
	{
	
		for (int i = 0; i < SpectrumAnalysis.Num(); i+=3)
		{
			if (SpectrumAnalysis.IsValidIndex(i) && SpectrumAnalysis.IsValidIndex(i + 3))
			{
				AveragedValue = (SpectrumAnalysis[i] + SpectrumAnalysis[i+1] + SpectrumAnalysis[i + 2]) / 3;
				AnalyzerData.Add(AveragedValue);
			}
		}
		

	}
	AudioSourceActor->SpectrumAnalysis = AnalyzerData;
	AudioSourceActor->CurrentTime = Modulous;
	//UpdateParamenterCollection(AnalyzerData);
}

void UAudioManagerObject::UpdateParamenterCollection(TArray<float> values)
{
	//FName ParameterName;
	//TArray<FName> Names;
	//
	//VisualizerMaterialParameter->GetParameterNames(Names,false);

	//for (int i = 0; i < AnalyzerData.Num(); i++)
	//{
	//		VisualizerMaterialParameterInstance->SetScalarParameterValue("Channel" + i, values[i]);		
	//}
	//
}


