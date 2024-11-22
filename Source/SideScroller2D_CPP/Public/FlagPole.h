// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "FlagPole.generated.h"

/**
 * 
 */
UCLASS()
class SIDESCROLLER2D_CPP_API AFlagPole : public APaperSpriteActor
{
	GENERATED_BODY()
public:
	AFlagPole();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* CollisionBox;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UPaperSpriteComponent* FlagSprite;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	// **타임라인 관련 변수**
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UTimelineComponent* Timeline; // 타임라인 컴포넌트
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UCurveFloat* FlagCurve; // 깃발 이동을 위한 곡선

	// **상태 관리**
	FVector FlagStartLocation; // 깃발의 초기 위치
	bool bFlagLowered = false; // 깃발이 내려갔는지 여부

	// 타임라인이 끝났는지 확인하는 변수
	bool bTimelineFinished = false;
	FVector PlayerEndLocation;
	FVector PlayerStartLocation;
	// **함수**
	UFUNCTION()
	void HandleFlagMovement(float Value); // 타임라인 콜백 함수

	UFUNCTION()
	void OnFlagLowered(); // 타임라인 완료 시 호출 함수


	
};
