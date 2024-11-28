// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseCameraModeArea.generated.h"

class UArrowComponent;
class UBoxComponent;

UCLASS()
class CAMERAMODESHOWCASE_API ABaseCameraModeArea : public AActor
{
	GENERATED_BODY()


	// Initializers
public:
	ABaseCameraModeArea();


	// UFunctions
public:
	UFUNCTION()
	virtual void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	                             const FHitResult& SweepResult) PURE_VIRTUAL();

	UFUNCTION()
	virtual void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) PURE_VIRTUAL();

	
	// UProperties
protected:
	UPROPERTY(EditAnywhere, Category="Custom")
	TObjectPtr<UBoxComponent> BoxCollider;

	UPROPERTY(EditAnywhere, Category="Custom")
	TObjectPtr<UArrowComponent> ArrowComponent;
};
