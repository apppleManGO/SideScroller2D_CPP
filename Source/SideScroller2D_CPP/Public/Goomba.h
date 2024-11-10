// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Goomba.generated.h"

/**
 * 
 */
UCLASS()
class SIDESCROLLER2D_CPP_API AGoomba : public APaperCharacter
{
	GENERATED_BODY()
public:
	AGoomba();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void Move();
	bool IsGroundAhead();

	UPROPERTY(EditAnywhere, Category = "Goomba")
	float MovementSpeed;

	// 3�� ���� �̵� �� ���߱� ���� �Լ�
	void StartMovingCycle();
	void StopMovingCycle();


	// �̵� ���¸� �����ϴ� ����
	bool bIsMoving;

	// ���� �̵� �ӵ��� �ּ� �� �ִ� ��
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MinSpeed=2.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxSpeed=5.0f;

	// Ÿ�̸� �ڵ鷯
	FTimerHandle MoveTimerHandle;

	bool bMovingRight;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
