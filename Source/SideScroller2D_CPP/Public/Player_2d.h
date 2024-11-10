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
	// ī�޶� �� (ī�޶�� ĳ���� ������ �Ÿ� ����)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	// ���� ī�޶� ������Ʈ
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* SideViewCamera;
	float InitialCameraZ;  // ī�޶��� �ʱ� Z ��ġ�� �����ϴ� ����
};
