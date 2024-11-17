// Fill out your copyright notice in the Description page of Project Settings.

#include "FlagPole.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Player_2d.h"
#include "GameFramework/CharacterMovementComponent.h"

AFlagPole::AFlagPole()
{
	PrimaryActorTick.bCanEverTick = false;

	// 충돌 박스 컴포넌트 생성 및 설정
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RootComponent); 
	CollisionBox->SetBoxExtent(FVector(10.0f, 10.0f, 200.0f));
	CollisionBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

	// 깃발 스프라이트 추가
	//FlagSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("FlagSprite"));
	//FlagSprite->SetupAttachment(RootComponent);

	// 충돌 이벤트 바인딩
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AFlagPole::OnOverlapBegin);
}
void AFlagPole::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		APlayer_2d* PlayerCharacter = Cast<APlayer_2d>(OtherActor);
		if (PlayerCharacter)
		{
			UE_LOG(LogTemp, Warning, TEXT("AFlagPole"));
			// 플레이어 이동 제한
			PlayerCharacter->GetCharacterMovement()->DisableMovement();
	
			// 깃발을 타고 내려오는 연출 시작
			FVector StartLocation = PlayerCharacter->GetActorLocation();
			FVector EndLocation = FVector(StartLocation.X, StartLocation.Y, -71.0f); // 내려가는 위치

			// 일정 시간 동안 위치 보간
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [=]()
			{
				PlayerCharacter->SetActorLocation(FMath::VInterpTo(PlayerCharacter->GetActorLocation(), EndLocation, GetWorld()->GetDeltaSeconds(), 1.0f));
			}, 0.01f, true, 0.0f);

			// 연출 후 게임 클리어
			//FTimerHandle ClearTimer;
			//GetWorld()->GetTimerManager().SetTimer(ClearTimer, [=]()
			//{
			//	UGameplayStatics::OpenLevel(this, FName("NextLevel"));
			//}, 3.0f, false);
		}
	}
}
