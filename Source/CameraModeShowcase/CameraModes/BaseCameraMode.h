// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCameraMode.generated.h"

class ACameraModeShowcaseCharacter;
struct FInputActionValue;
/**
 * 
 */
UCLASS(Abstract)
class CAMERAMODESHOWCASE_API UBaseCameraMode : public UObject
{
	GENERATED_BODY()


	// Virtuals
public:
	virtual void HandleLook(const FInputActionValue& Value) PURE_VIRTUAL();
	virtual void HandleMove(const FInputActionValue& Value) PURE_VIRTUAL();
	virtual void HandleTick(const float& DeltaSeconds) PURE_VIRTUAL();
	virtual void EnterMode(const float& YawRotation) PURE_VIRTUAL();

	
	// Member Pointers
public:
	TObjectPtr<ACameraModeShowcaseCharacter> Owner;


	// Member Variables
public:
	FRotator TargetRotation;

protected:
	bool bShouldTick = false;
};
