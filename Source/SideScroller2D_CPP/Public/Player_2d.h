// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Player_2d.generated.h"

/**
 * 
 */
UCLASS()
class SIDESCROLLER2D_CPP_API APlayer_2d : public APaperCharacter
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	APlayer_2d();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void MoveRight(float Value);
	void StartJump();
	void StopJump();
	// 카메라 붐 (카메라와 캐릭터 사이의 거리 조정)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	// 실제 카메라 컴포넌트
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCamera;
	float InitialCameraZ;  // 카메라의 초기 Z 위치를 저장하는 변수
};
