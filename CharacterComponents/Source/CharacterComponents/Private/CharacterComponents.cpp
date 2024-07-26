// Copyright Epic Games, Inc. All Rights Reserved.

#include "CharacterComponents.h"

#define LOCTEXT_NAMESPACE "FCharacterComponentsModule"

void FCharacterComponentsModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FCharacterComponentsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCharacterComponentsModule, CharacterComponents)