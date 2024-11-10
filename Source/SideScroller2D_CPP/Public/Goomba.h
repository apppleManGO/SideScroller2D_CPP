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

	// 3초 동안 이동 후 멈추기 위한 함수
	void StartMovingCycle();
	void StopMovingCycle();


	// 이동 상태를 제어하는 변수
	bool bIsMoving;

	// 랜덤 이동 속도의 최소 및 최대 값
	UPROPERTY(EditAnywhere, Category = "Movement")
	float MinSpeed=2.0f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float MaxSpeed=5.0f;

	// 타이머 핸들러
	FTimerHandle MoveTimerHandle;

	bool bMovingRight;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
