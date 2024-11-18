// Fill out your copyright notice in the Description page of Project Settings.

#include "FlagPole.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Player_2d.h"
#include "PaperSpriteComponent.h"
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
	FlagSprite = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("FlagSprite"));
	FlagSprite->SetupAttachment(RootComponent);

	// 충돌 이벤트 바인딩
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AFlagPole::OnOverlapBegin);
}
void AFlagPole::BeginPlay()
{
	FlagStartLocation=FlagSprite->GetComponentLocation();
}
void AFlagPole::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		APlayer_2d* PlayerCharacter = Cast<APlayer_2d>(OtherActor);
		if (PlayerCharacter)
		{
			// 플레이어 이동 제한
			PlayerCharacter->GetCharacterMovement()->DisableMovement();


			// 깃발을 타고 내려오는 연출 시작
			FVector StartLocation = PlayerCharacter->GetActorLocation();
			FVector EndLocationZ = FVector(StartLocation.X, StartLocation.Y, -41.0f); // 내려가는 위치
			FVector EndFlagLocationZ = FVector(FlagStartLocation.X, FlagStartLocation.Y, -41.0f); // 깃발 내려가는 위치



			//FVector EndLocationX = FVector(3073.0f, StartLocation.Y, EndLocationZ.Z); // X축으로 이동하는 위치
			// 
			// 일정 시간 동안 위치 이동
			FTimerHandle TimerHandle;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, PlayerCharacter, EndLocationZ, EndFlagLocationZ]()
				{
					//플레이어 위치 이동
					FVector CurrentPlayerLocation = PlayerCharacter->GetActorLocation();
					FVector NewPlayerLocation = FMath::VInterpTo(CurrentPlayerLocation, EndLocationZ, GetWorld()->GetDeltaSeconds(), 1.0f);
					PlayerCharacter->SetActorLocation(NewPlayerLocation);

					// 깃발 위치 이동
					FVector CurrentFlagLocation = FlagSprite->GetComponentLocation();
					FVector NewFlagLocation = FMath::VInterpTo(CurrentFlagLocation, EndFlagLocationZ, GetWorld()->GetDeltaSeconds(), 1.0f);
					FlagSprite->SetWorldLocation(NewFlagLocation);


					if (FMath::Abs(NewPlayerLocation.Z - EndLocationZ.Z) < 1.0f)
					{
						PlayerCharacter->GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
						PlayerCharacter->SetActorLocation(FVector(2978,100,-63));
						//FVector EndLocationX = FVector(3073.0f, 100, -71.0); // Z축 유지, X축으로 이동

						//// X축 이동을 위한 타이머 설정
						//FTimerHandle TimerHandleX;
						//GetWorld()->GetTimerManager().SetTimer(TimerHandleX, [this, PlayerCharacter, NewPlayerLocation, EndLocationX]()
						//	{
						//		FVector CurrentLocation = PlayerCharacter->GetActorLocation();

						//		// X축으로 자연스럽게 이동
						//		FVector NewLocationX = FMath::VInterpTo(CurrentLocation, EndLocationX, GetWorld()->GetDeltaSeconds(), 2.0f);
						//		PlayerCharacter->SetActorLocation(NewLocationX);

						//		// X축 이동이 끝났다면 타이머 종료
						//		if (FMath::Abs(NewLocationX.X - EndLocationX.X) < 5.0f)
						//		{
						//			UKismetSystemLibrary::QuitGame(this, 0, EQuitPreference::Quit, false);

						//		}
						//	}, 0.03f, true, 0.0f);
						// Z축 위치 이동 타이머 종료
						//GetWorld()->GetTimerManager().ClearTimer(TimerHandle);
					}

				}, 0.01f, true, 0.0f);

			
			// 특정 방향으로의 이동 벡터
			FVector Direction = FVector(1.0f, 0.0f, 0.0f); // x축으로 이동
			PlayerCharacter->AddMovementInput(Direction, 1.0f); // 이동

			// 연출 후 게임 클리어
			//FTimerHandle ClearTimer;
			//GetWorld()->GetTimerManager().SetTimer(ClearTimer, [=]()
			//{
			//	UGameplayStatics::OpenLevel(this, FName("NextLevel"));
			//}, 3.0f, false);
		}
	}
}
