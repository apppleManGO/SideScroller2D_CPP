// Copyright Epic Games, Inc. All Rights Reserved.

#include "SideScroller2D_CPPGameMode.h"
#include "SideScroller2D_CPPCharacter.h"
#include "UObject/ConstructorHelpers.h"

#include "Engine/World.h"

ASideScroller2D_CPPGameMode::ASideScroller2D_CPPGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	RemainingTime = 60; // 1분 = 60초

}

void ASideScroller2D_CPPGameMode::addCoinScore()
{
	score += 100;
}
void ASideScroller2D_CPPGameMode::BeginPlay()
{
    Super::BeginPlay();

    // 1초 간격으로 DecrementTimer 함수 실행
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASideScroller2D_CPPGameMode::DecrementTimer, 1.0f, true);
}

void ASideScroller2D_CPPGameMode::DecrementTimer()
{
    RemainingTime--;

    // 남은 시간 출력 (디버그용)
    //UE_LOG(LogTemp, Log, TEXT("Remaining Time: %d seconds"), RemainingTime);

    if (RemainingTime <= 0)
    {
        OnTimeUp();
    }
}

void ASideScroller2D_CPPGameMode::OnTimeUp()
{
    // 타이머 정지
    GetWorld()->GetTimerManager().ClearTimer(TimerHandle);

    // 게임 종료 처리 또는 다른 로직 추가
    UE_LOG(LogTemp, Warning, TEXT("Time is up! Game Over."));
}