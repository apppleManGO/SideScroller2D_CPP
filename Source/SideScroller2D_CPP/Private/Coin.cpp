// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

ACoin::ACoin()
{
    PrimaryActorTick.bCanEverTick = false;

    // �浹 �ڽ� ����
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    CollisionBox->SetupAttachment(RootComponent); // �⺻ ��������Ʈ�� ����
    CollisionBox->SetBoxExtent(FVector(9.0f, 9.0f, 9.0f));
    CollisionBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

    // �浹 �̺�Ʈ ����
    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ACoin::OnOverlapBegin);

    //// ���� �ùķ��̼� ��Ȱ��ȭ
    CollisionBox->SetSimulatePhysics(false); 
   

}

void ACoin::BeginPlay()
{
    Super::BeginPlay();
}

void ACoin::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // �÷��̾�� �浹�ߴ��� Ȯ�� (OtherActor �˻�)
    if (OtherActor && OtherActor != this)
    {
        // ����: ���� �߰��ϴ� �ڵ� (���⼱ �α׷� ǥ��)
        UE_LOG(LogTemp, Warning, TEXT("Player collected a coin! Score: %d"), CoinValue);

        // ���� ����
        Destroy();
    }
}