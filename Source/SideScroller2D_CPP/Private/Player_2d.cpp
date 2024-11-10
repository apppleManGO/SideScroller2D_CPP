// Fill out your copyright notice in the Description page of Project Settings.

#include "Player_2d.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

APlayer_2d::APlayer_2d()
{
    // 카메라 붐 생성 및 초기화 (캐릭터를 따라다니게 설정)
    CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
    CameraBoom->SetupAttachment(RootComponent);
    CameraBoom->TargetArmLength = 200.0f;  // 카메라와 캐릭터 사이의 거리 설정
    CameraBoom->bDoCollisionTest = false;  // 충돌 테스트를 비활성화하여 카메라가 장애물에 막히지 않도록 함
    CameraBoom->SetUsingAbsoluteRotation(true);  // 카메라를 고정된 방향으로 유지
    CameraBoom->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));  // 카메라를 측면에서 바라보도록 회전 설정

    // 카메라 컴포넌트 생성 및 초기화
    SideViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("SideViewCamera"));
    SideViewCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
    SideViewCamera->bUsePawnControlRotation = false;  // 카메라가 캐릭터의 회전에 영향받지 않도록 설정


    // 캐릭터가 중력을 사용하도록 설정
    GetCharacterMovement()->GravityScale = 2.0f;

    //Jump Z Velocity 설정
    GetCharacterMovement()->JumpZVelocity = 600.0f;
    // 캐릭터의 이동 속도 설정
    GetCharacterMovement()->MaxWalkSpeed = 300.0f;

    // 공중 제어 설정 (점프 중에도 약간의 조작이 가능하도록)
    GetCharacterMovement()->AirControl = 0.8f;

    // 캐릭터가 이동 방향에 따라 회전하도록 설정
    bUseControllerRotationYaw = false;

    // 다른 이동 속성 설정
    GetCharacterMovement()->bOrientRotationToMovement = true; // 이동 방향에 따라 회전
}
void APlayer_2d::BeginPlay()
{
    Super::BeginPlay();

    // 카메라의 초기 Z 위치 저장
    InitialCameraZ = SideViewCamera->GetComponentLocation().Z;
}
void APlayer_2d::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 카메라의 Z 위치를 고정하여 상하 움직임을 방지
    FVector CameraLocation = SideViewCamera->GetComponentLocation();
    CameraLocation.Z = InitialCameraZ;  // 초기 Z 위치로 고정
    SideViewCamera->SetWorldLocation(CameraLocation);
}

void APlayer_2d::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // 오른쪽으로 이동하는 입력 바인딩
    PlayerInputComponent->BindAxis("MoveRight", this, &APlayer_2d::MoveRight);

    // 점프 입력 바인딩
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayer_2d::StartJump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayer_2d::StopJump);
}
void APlayer_2d::MoveRight(float Value)
{
    // 오른쪽으로 이동
    AddMovementInput(FVector(1.0f, 0.0f, 0.0f), Value);

    // 캐릭터가 이동 방향을 바라보도록 회전 설정
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
