// Copyright Epic Games, Inc. All Rights Reserved.

#include "TFS_GOAP.h"

#define LOCTEXT_NAMESPACE "FTFS_GOAPModule"

void FTFS_GOAPModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FTFS_GOAPModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FTFS_GOAPModule, TFS_GOAP)