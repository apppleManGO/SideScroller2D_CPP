// Fill out your copyright notice in the Description page of Project Settings.

#include "FlagPole.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Player_2d.h"
#include "PaperSpriteComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/TimelineComponent.h"

AFlagPole::AFlagPole()
{
	PrimaryActorTick.bCanEverTick = true;

	// 충돌 박스 컴포넌트 생성 및 설정
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent); 
	CollisionBox->SetBoxExtent(FVector(10.0f, 10.0f, 200.0f));
	CollisionBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	// 깃발 스프라이트 추가
	FlagSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("FlagSprite"));
	FlagSprite->SetupAttachment(RootComponent);

	// 충돌 이벤트 바인딩
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AFlagPole::OnOverlapBegin);

	Timeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("Timeline"));
}
void AFlagPole::BeginPlay()
{
	Super::BeginPlay();

	if (FlagCurve)
	{
		// 타임라인 이벤트에 함수 바인딩
		FOnTimelineFloat ProgressFunction;
		ProgressFunction.BindUFunction(this, FName("HandleFlagMovement"));
		Timeline->AddInterpFloat(FlagCurve, ProgressFunction);

		FOnTimelineEvent TimelineFinishedEvent;
		TimelineFinishedEvent.BindUFunction(this, FName("OnFlagLowered"));
		Timeline->SetTimelineFinishedFunc(TimelineFinishedEvent);


	}
}

void AFlagPole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    
	if (Timeline)
	{
		Timeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, nullptr);
	}
}

void AFlagPole::HandleFlagMovement(float Value)
{
	if (FlagSprite)
	{
		FVector NewLocation = FlagStartLocation;
		NewLocation.Z -= (Value * 120.0f); // 60.0f 값으로 조정하여 Z축 이동 범위를 크게 설정
		FlagSprite->SetWorldLocation(NewLocation);
	}
	if (APlayer_2d* PlayerCharacter = Cast<APlayer_2d>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0)))  // 플레이어 캐릭터 찾기
	{
		// 플레이어 이동
		FVector NewPlayerLocation = PlayerStartLocation;
		NewPlayerLocation.Z -= (Value * 120.0f); // 플레이어도 같은 비율로 내려가도록 설정
		PlayerCharacter->SetActorLocation(NewPlayerLocation);
		// 플레이어가 지정한 위치에 도달했는지 체크
                if (NewPlayerLocation.Z <= PlayerEndLocation.Z)
                {
                    if (!bTimelineFinished)
                    {
                        bTimelineFinished = true;
                        Timeline->Stop(); // 타임라인 종료
                        OnFlagLowered(); // 상태 업데이트
                    }
                }
	}
}

void AFlagPole::OnFlagLowered()
{
	bFlagLowered = true; // 상태 업데이트
	// 이후 캐릭터 이동 처리
}
void AFlagPole::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		APlayer_2d* PlayerCharacter = Cast<APlayer_2d>(OtherActor);
		if (PlayerCharacter && !bFlagLowered)  // 깃발이 이미 내려졌는지 체크
		{
			// 플레이어의 시작 위치와 목표 위치 설정
			PlayerStartLocation = PlayerCharacter->GetActorLocation();
			PlayerEndLocation = FVector(PlayerStartLocation.X, PlayerStartLocation.Y, -50.0f); // Z축을 -50으로 설정

			// 타임라인 재생 시작
			if (FlagCurve && Timeline)
			{
				FlagStartLocation = FlagSprite->GetComponentLocation(); // 시작 위치 저장
				PlayerStartLocation = PlayerCharacter->GetActorLocation(); // 플레이어의 시작 위치 저장
				Timeline->Play();
				
			}
			bFlagLowered = true;  // 깃발이 내려졌다고 표시
		}
	}
}