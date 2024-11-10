// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "SpawnBlock.generated.h"

/**
 * 
 */
UCLASS()
class SIDESCROLLER2D_CPP_API ASpawnBlock : public APaperSpriteActor
{
	GENERATED_BODY()
public:
	ASpawnBlock();
	virtual void BeginPlay() override;
    UPROPERTY(EditAnywhere, Category = "Spawn")
    TSubclassOf<AActor> CoinClass; // 소환할 코인 클래스

    UPROPERTY(EditAnywhere, Category = "Spawn")
    TSubclassOf<AActor> MushroomClass; // 소환할 버섯 클래스

    UFUNCTION()
    void OnBlockHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    UPROPERTY(VisibleAnywhere)
    class UBoxComponent* CollisionBox;
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UPaperSpriteComponent* Sprite;
    bool bHasSpawnedItem; // 아이템이 한 번만 소환되도록 체크하는 변수

 

};
