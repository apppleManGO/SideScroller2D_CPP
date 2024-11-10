// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnBlock.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


ASpawnBlock::ASpawnBlock()
{
    PrimaryActorTick.bCanEverTick = false;


    // 충돌 박스 컴포넌트 생성 및 스프라이트 컴포넌트에 부모로 설정
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    CollisionBox->SetupAttachment(RootComponent); // 기본 스프라이트에 연결

    CollisionBox->SetBoxExtent(FVector(8.0f, 8.0f, 8.0f));
    CollisionBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));


    // 충돌 이벤트 바인딩
    CollisionBox->OnComponentHit.AddDynamic(this, &ASpawnBlock::OnBlockHit);

    bHasSpawnedItem = false; // 아이템 소환 여부 초기화

   
}

void ASpawnBlock::BeginPlay()
{
    Super::BeginPlay();
}

void ASpawnBlock::OnBlockHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (bHasSpawnedItem) return; // 이미 소환되었으면 종료
    UE_LOG(LogTemp, Warning, TEXT("Hit Normal Z: %f"), Hit.Normal.Z);
    // 플레이어가 블록을 아래에서 쳤을 때만 아이템을 소환
    if (OtherActor && OtherActor != this && Hit.Normal.Z > 0)
    {
        bHasSpawnedItem = true; // 아이템이 소환됨을 표시

        // 코인 또는 버섯 소환
        FVector SpawnLocation = GetActorLocation() + FVector(0.0f, 0.0f, 20.0f);
        FRotator SpawnRotation = FRotator::ZeroRotator;

        if (CoinClass)
        {
            GetWorld()->SpawnActor<AActor>(CoinClass, SpawnLocation, SpawnRotation);
        }
        else if (MushroomClass)
        {
            GetWorld()->SpawnActor<AActor>(MushroomClass, SpawnLocation, SpawnRotation);
        }
    }
}