// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

ACoin::ACoin()
{
    PrimaryActorTick.bCanEverTick = false;

    // 충돌 박스 설정
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    CollisionBox->SetupAttachment(RootComponent); // 기본 스프라이트에 연결
    CollisionBox->SetBoxExtent(FVector(9.0f, 9.0f, 9.0f));
    CollisionBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

    // 충돌 이벤트 연결
    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnOverlapBegin);

    //// 물리 시뮬레이션 비활성화
    CollisionBox->SetSimulatePhysics(false); 
   

}

void ACoin::BeginPlay()
{
    Super::BeginPlay();
}

void ACoin::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // 플레이어와 충돌했는지 확인 (OtherActor 검사)
    if (OtherActor && OtherActor != this)
    {
        // 예시: 점수 추가하는 코드 (여기선 로그로 표시)
        UE_LOG(LogTemp, Warning, TEXT("Player collected a coin! Score: %d"), CoinValue);

        // 코인 제거
        Destroy();
    }
}