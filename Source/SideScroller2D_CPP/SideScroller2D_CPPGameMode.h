// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SideScroller2D_CPPGameMode.generated.h"

UCLASS(minimalapi)
class ASideScroller2D_CPPGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASideScroller2D_CPPGameMode();

	int32 score = 0;

	void addCoinScore();
};



