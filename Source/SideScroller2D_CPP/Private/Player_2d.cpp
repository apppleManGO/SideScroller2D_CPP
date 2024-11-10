// Fill out your copyright notice in the Description page of Project Settings.

#include "Player_2d.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APlayer_2d::APlayer_2d()
{
    // ī�޶� �� ���� �� �ʱ�ȭ (ĳ���͸� ����ٴϰ� ����)
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 200.0f;  // ī�޶�� ĳ���� ������ �Ÿ� ����
    CameraBoom->bDoCollisionTest = false;  // �浹 �׽�Ʈ�� ��Ȱ��ȭ�Ͽ� ī�޶� ��ֹ��� ������ �ʵ��� ��
    CameraBoom->SetUsingAbsoluteRotation(true);  // ī�޶� ������ �������� ����
    CameraBoom->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));  // ī�޶� ���鿡�� �ٶ󺸵��� ȸ�� ����

    // ī�޶� ������Ʈ ���� �� �ʱ�ȭ
    SideViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
    SideViewCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    SideViewCamera->bUsePawnControlRotation = false;  // ī�޶� ĳ������ ȸ���� ������� �ʵ��� ����


    // ĳ���Ͱ� �߷��� ����ϵ��� ����
    GetCharacterMovement()->GravityScale = 2.0f;

    //Jump Z Velocity ����
    GetCharacterMovement()->JumpZVelocity = 600.0f;
    // ĳ������ �̵� �ӵ� ����
    GetCharacterMovement()->MaxWalkSpeed = 300.0f;

    // ���� ���� ���� (���� �߿��� �ణ�� ������ �����ϵ���)
    GetCharacterMovement()->AirControl = 0.8f;

    // ĳ���Ͱ� �̵� ���⿡ ���� ȸ���ϵ��� ����
    bUseControllerRotationYaw = false;

    // �ٸ� �̵� �Ӽ� ����
    GetCharacterMovement()->bOrientRotationToMovement = true; // �̵� ���⿡ ���� ȸ��
}
void APlayer_2d::BeginPlay()
{
    Super::BeginPlay();

    // ī�޶��� �ʱ� Z ��ġ ����
    InitialCameraZ = SideViewCamera->GetComponentLocation().Z;
}
void APlayer_2d::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // ī�޶��� Z ��ġ�� �����Ͽ� ���� �������� ����
    FVector CameraLocation = SideViewCamera->GetComponentLocation();
    CameraLocation.Z = InitialCameraZ;  // �ʱ� Z ��ġ�� ����
    SideViewCamera->SetWorldLocation(CameraLocation);
}

void APlayer_2d::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // ���������� �̵��ϴ� �Է� ���ε�
    PlayerInputComponent->BindAxis("MoveRight", this, &APlayer_2d::MoveRight);

    // ���� �Է� ���ε�
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayer_2d::StartJump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayer_2d::StopJump);
}
void APlayer_2d::MoveRight(float Value)
{
    // ���������� �̵�
    AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);

    // ĳ���Ͱ� �̵� ������ �ٶ󺸵��� ȸ�� ����
    if (Value != 0.0f)
    {
        SetActorRotation(FRotator(0.0f, (Value > 0.0f ? 0.0f : 180.0f), 0.0f));
    }
}

void APlayer_2d::StartJump()
{
    bPressedJump = true;
}

void APlayer_2d::StopJump()
{
    bPressedJump = false;
}
