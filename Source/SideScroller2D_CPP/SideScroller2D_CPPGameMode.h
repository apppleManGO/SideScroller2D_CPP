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
	virtual void BeginPlay() override;
	int32 score = 0;

	void addCoinScore();

	// 타이머 관련
	FTimerHandle TimerHandle;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 RemainingTime;

	void DecrementTimer();
	void OnTimeUp();

};



