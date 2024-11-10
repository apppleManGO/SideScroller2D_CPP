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
    TSubclassOf<AActor> CoinClass; // ��ȯ�� ���� Ŭ����

    UPROPERTY(EditAnywhere, Category = "Spawn")
    TSubclassOf<AActor> MushroomClass; // ��ȯ�� ���� Ŭ����

    UFUNCTION()
    void OnBlockHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
    UPROPERTY(VisibleAnywhere)
    class UBoxComponent* CollisionBox;
    UPROPERTY(VisibleAnywhere, Category = "Components")
    class UPaperSpriteComponent* Sprite;
    bool bHasSpawnedItem; // �������� �� ���� ��ȯ�ǵ��� üũ�ϴ� ����

 

};
