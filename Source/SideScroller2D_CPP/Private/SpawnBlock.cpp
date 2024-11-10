// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnBlock.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"


ASpawnBlock::ASpawnBlock()
{
    PrimaryActorTick.bCanEverTick = false;


    // �浹 �ڽ� ������Ʈ ���� �� ��������Ʈ ������Ʈ�� �θ�� ����
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    CollisionBox->SetupAttachment(RootComponent); // �⺻ ��������Ʈ�� ����

    CollisionBox->SetBoxExtent(FVector(8.0f, 8.0f, 8.0f));
    CollisionBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));


    // �浹 �̺�Ʈ ���ε�
    CollisionBox->OnComponentHit.AddDynamic(this, &ASpawnBlock::OnBlockHit);

    bHasSpawnedItem = false; // ������ ��ȯ ���� �ʱ�ȭ

   
}

void ASpawnBlock::BeginPlay()
{
    Super::BeginPlay();
}

void ASpawnBlock::OnBlockHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (bHasSpawnedItem) return; // �̹� ��ȯ�Ǿ����� ����
    UE_LOG(LogTemp, Warning, TEXT("Hit Normal Z: %f"), Hit.Normal.Z);
    // �÷��̾ ����� �Ʒ����� ���� ���� �������� ��ȯ
    if (OtherActor && OtherActor != this && Hit.Normal.Z > 0)
    {
        bHasSpawnedItem = true; // �������� ��ȯ���� ǥ��

        // ���� �Ǵ� ���� ��ȯ
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