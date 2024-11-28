// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCameraModeArea.h"
#include "TopDownCameraModeArea.generated.h"

/**
 * 
 */
UCLASS()
class CAMERAMODESHOWCASE_API ATopDownCameraModeArea : public ABaseCameraModeArea
{
	GENERATED_BODY()


	// UFunctions
public:
	virtual void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
	virtual void OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
};
