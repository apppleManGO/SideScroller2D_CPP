// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "Coin.generated.h"

/**
 * 
 */
UCLASS()
class SIDESCROLLER2D_CPP_API ACoin : public APaperSpriteActor
{
	GENERATED_BODY()
public:
	ACoin();
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, Category = "Coin")
	int32 CoinValue = 100; // 코인 점수 값

};
