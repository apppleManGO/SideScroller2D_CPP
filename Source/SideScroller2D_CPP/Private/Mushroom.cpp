// Fill out your copyright notice in the Description page of Project Settings.


#include "Mushroom.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"
AMushroom::AMushroom()
{
    PrimaryActorTick.bCanEverTick = false;

    // �浹 �ڽ� ����
    CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
    CollisionBox->SetupAttachment(RootComponent); // �⺻ ��������Ʈ�� ����
    CollisionBox->SetBoxExtent(FVector(9.0f, 9.0f, 9.0f));
    CollisionBox->SetCollisionProfileName(TEXT("OverlapAllDynamic"));

    // �浹 �̺�Ʈ ����
    CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &AMushroom::OnOverlapBegin);
}

void AMushroom::BeginPlay()
{
    Super::BeginPlay();
}

void AMushroom::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // �÷��̾�� �浹�ߴ��� Ȯ��
    if (OtherActor && OtherActor != this)
    {
        UE_LOG(LogTemp, Warning, TEXT("Player!"));
        ACharacter* PlayerCharacter = Cast<ACharacter>(OtherActor);
        if (PlayerCharacter)
        {
            // ĳ���� ũ�� ����
            PlayerCharacter->GetCapsuleComponent()->SetWorldScale3D(FVector(GrowthFactor));
            UE_LOG(LogTemp, Warning, TEXT("Player collected a mushroom and grew bigger!"));

            // ���� ����
            Destroy();
        }
    }
}