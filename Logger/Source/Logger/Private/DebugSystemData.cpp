// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugSystemData.h"

UDebugSystemData::UDebugSystemData()
{
	//init variable.
	DebugCategoryMap.Empty();
	for (EDebugCategory Category : TEnumRange<EDebugCategory>())
	{
		if (Category != EDebugCategory::MAX)
		{
			DebugCategoryMap.Add(Category, false);
		}
	}


}