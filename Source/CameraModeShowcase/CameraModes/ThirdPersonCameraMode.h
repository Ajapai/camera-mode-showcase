// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCameraMode.h"
#include "ThirdPersonCameraMode.generated.h"

/**
 * 
 */
UCLASS()
class CAMERAMODESHOWCASE_API UThirdPersonCameraMode : public UBaseCameraMode
{
	GENERATED_BODY()


	// Overrides
public:
	virtual void HandleLook(const FInputActionValue& Value) override;
	virtual void HandleMove(const FInputActionValue& Value) override;
	virtual void HandleTick(const float& DeltaSeconds) override;
	virtual void EnterMode(const float& YawRotation = 0) override;

	
	// Member Variables
protected:
	float TargetArmLength = 400;

private:
	bool bShouldInterpolateRotation;
};
