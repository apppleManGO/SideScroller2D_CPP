// Fill out your copyright notice in the Description page of Project Settings.


#include "Goomba.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Components/CapsuleComponent.h"
#include "TimerManager.h"
#include "Player_2d.h"

AGoomba::AGoomba()
{
    PrimaryActorTick.bCanEverTick = true;

    MovementSpeed = 1.0f;
    bMovingRight = true;

    GetCharacterMovement()->bOrientRotationToMovement = false;
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 180.0f, 0.0f);
}

void AGoomba::BeginPlay()
{
    Super::BeginPlay();
    // 처음에 3초 후 이동 시작
    StartMovingCycle();
}

void AGoomba::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 바닥이 없는 경우 방향을 바꿈
    if (!IsGroundAhead())
    {
        bMovingRight = !bMovingRight;
        SetActorScale3D(FVector(bMovingRight ? 1.0f : -1.0f, 1.0f, 1.0f));
    }
    // 이동 중일 때만 이동
    if (bIsMoving)
    {
        // 현재 이동 방향에 따라 속도 설정
        float Direction = bMovingRight ? 1.0f : -1.0f;
        AddMovementInput(FVector(Direction, 0.0f, 0.0f), MovementSpeed * DeltaTime);
    }
}

void AGoomba::StartMovingCycle()
{
    //이동할 방향을 랜덤으로 설정
    bMovingRight = FMath::RandBool();

    // 이동 상태가 아니면 이동 시작
    if (!bIsMoving)
    {
        // 이동 속도를 2~5 사이의 랜덤 값으로 설정
        MovementSpeed = FMath::RandRange(MinSpeed, MaxSpeed);
        bIsMoving = true;

        // 3초 동안 이동 후 멈추는 함수 예약
        GetWorldTimerManager().SetTimer(MoveTimerHandle, this, &AGoomba::StopMovingCycle, 3.0f, false);
    }
}
void AGoomba::StopMovingCycle()
{
    // 이동을 멈추고 속도 초기화
    MovementSpeed = 0.0f;
    bIsMoving = false;

    // 3초 후 다시 이동 시작
    GetWorldTimerManager().SetTimer(MoveTimerHandle, this, &AGoomba::StartMovingCycle, 3.0f, false);
}
bool AGoomba::IsGroundAhead()
{
    FVector Start = GetActorLocation();
    FVector End = Start + FVector(bMovingRight ? 50.0f : -50.0f, 0.0f, -50.0f);

    FHitResult Hit;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(this);

    // 바닥 확인을 위해 라인 트레이스 실행
    return GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, CollisionParams);
}
void AGoomba::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // 충돌한 Actor가 플레이어인지 확인
    if (OtherActor && OtherActor != this)
    {
        // 플레이어가 위에서 Goomba를 밟았을 때만 처리
        FVector PlayerLocation = OtherActor->GetActorLocation();
        FVector GoombaLocation = GetActorLocation();
        UE_LOG(LogTemp, Warning, TEXT("OnOverlapBegin"));
        if (PlayerLocation.Z > GoombaLocation.Z) // 플레이어가 더 높은 위치에서 충돌할 경우
        {
            // Goomba 제거
            Destroy();
            UE_LOG(LogTemp, Warning, TEXT("Destroy"));
            // 플레이어에게 반발력 적용 (점프 효과)
            APlayer_2d* PlayerCharacter = Cast<APlayer_2d>(OtherActor);
            if (PlayerCharacter)
            {
                PlayerCharacter->LaunchCharacter(FVector(0.0f, 0.0f, 300.0f), false, true);
            }
        }
    }
}