// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "Mushroom.generated.h"

/**
 * 
 */
UCLASS()
class SIDESCROLLER2D_CPP_API AMushroom : public APaperSpriteActor
{
	GENERATED_BODY()
public:
	AMushroom();
	virtual void BeginPlay() override;
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, Category = "Mushroom")
	float GrowthFactor = 1.5f; // 플레이어 크기 증가 값
};
