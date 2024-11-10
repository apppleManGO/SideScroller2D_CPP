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
    // ó���� 3�� �� �̵� ����
    StartMovingCycle();
}

void AGoomba::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // �ٴ��� ���� ��� ������ �ٲ�
    if (!IsGroundAhead())
    {
        bMovingRight = !bMovingRight;
        SetActorScale3D(FVector(bMovingRight ? 1.0f : -1.0f, 1.0f, 1.0f));
    }
    // �̵� ���� ���� �̵�
    if (bIsMoving)
    {
        // ���� �̵� ���⿡ ���� �ӵ� ����
        float Direction = bMovingRight ? 1.0f : -1.0f;
        AddMovementInput(FVector(Direction, 0.0f, 0.0f), MovementSpeed * DeltaTime);
    }
}

void AGoomba::StartMovingCycle()
{
    //�̵��� ������ �������� ����
    bMovingRight = FMath::RandBool();

    // �̵� ���°� �ƴϸ� �̵� ����
    if (!bIsMoving)
    {
        // �̵� �ӵ��� 2~5 ������ ���� ������ ����
        MovementSpeed = FMath::RandRange(MinSpeed, MaxSpeed);
        bIsMoving = true;

        // 3�� ���� �̵� �� ���ߴ� �Լ� ����
        GetWorldTimerManager().SetTimer(MoveTimerHandle, this, &AGoomba::StopMovingCycle, 3.0f, false);
    }
}
void AGoomba::StopMovingCycle()
{
    // �̵��� ���߰� �ӵ� �ʱ�ȭ
    MovementSpeed = 0.0f;
    bIsMoving = false;

    // 3�� �� �ٽ� �̵� ����
    GetWorldTimerManager().SetTimer(MoveTimerHandle, this, &AGoomba::StartMovingCycle, 3.0f, false);
}
bool AGoomba::IsGroundAhead()
{
    FVector Start = GetActorLocation();
    FVector End = Start + FVector(bMovingRight ? 50.0f : -50.0f, 0.0f, -50.0f);

    FHitResult Hit;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(this);

    // �ٴ� Ȯ���� ���� ���� Ʈ���̽� ����
    return GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_Visibility, CollisionParams);
}
void AGoomba::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // �浹�� Actor�� �÷��̾����� Ȯ��
    if (OtherActor && OtherActor != this)
    {
        // �÷��̾ ������ Goomba�� ����� ���� ó��
        FVector PlayerLocation = OtherActor->GetActorLocation();
        FVector GoombaLocation = GetActorLocation();
        UE_LOG(LogTemp, Warning, TEXT("OnOverlapBegin"));
        if (PlayerLocation.Z > GoombaLocation.Z) // �÷��̾ �� ���� ��ġ���� �浹�� ���
        {
            // Goomba ����
            Destroy();
            UE_LOG(LogTemp, Warning, TEXT("Destroy"));
            // �÷��̾�� �ݹ߷� ���� (���� ȿ��)
            APlayer_2d* PlayerCharacter = Cast<APlayer_2d>(OtherActor);
            if (PlayerCharacter)
            {
                PlayerCharacter->LaunchCharacter(FVector(0.0f, 0.0f, 300.0f), false, true);
            }
        }
    }
}