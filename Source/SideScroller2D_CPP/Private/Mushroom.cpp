// Fill out your copyright notice in the Description page of Project Settings.


#include "Mushroom.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
AMushroom::AMushroom()
{
    PrimaryActorTick.bCanEverTick = false;

    // 충돌 박스 설정
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    CollisionBox->SetupAttachment(RootComponent); // 기본 스프라이트에 연결
    CollisionBox->SetBoxExtent(FVector(9.0f, 9.0f, 9.0f));
    CollisionBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

    // 충돌 이벤트 연결
    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AMushroom::OnOverlapBegin);
}

void AMushroom::BeginPlay()
{
    Super::BeginPlay();
}

void AMushroom::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // 플레이어와 충돌했는지 확인
    if (OtherActor && OtherActor != this)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player!"));
        ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor);
        if (PlayerCharacter)
        {
            // 캐릭터 크기 증가
            PlayerCharacter->GetCapsuleComponent()->SetWorldScale3D(FVector(GrowthFactor));
            UE_LOG(LogTemp, Warning, TEXT("Player collected a mushroom and grew bigger!"));

            // 버섯 제거
            Destroy();
        }
    }
}