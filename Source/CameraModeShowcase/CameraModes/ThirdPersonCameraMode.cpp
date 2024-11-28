// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonCameraMode.h"

#include "InputActionValue.h"
#include "CameraModeShowcase/CameraModeShowcaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"

void UThirdPersonCameraMode::HandleLook(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Owner->Controller != nullptr)
	{
		// add yaw and pitch input to controller
		Owner->AddControllerYawInput(LookAxisVector.X);
		Owner->AddControllerPitchInput(LookAxisVector.Y);
	}
}

void UThirdPersonCameraMode::HandleMove(const FInputActionValue& Value)
{
	if (bShouldTick) return;
	
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Owner->Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Owner->Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		Owner->AddMovementInput(ForwardDirection, MovementVector.Y);
		Owner->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void UThirdPersonCameraMode::HandleTick(const float& DeltaSeconds)
{
	if (!bShouldTick) return;
	
	Owner->CameraBoom->TargetArmLength = FMath::FInterpTo(Owner->CameraBoom->TargetArmLength, TargetArmLength, DeltaSeconds, 1.5);

	if (Owner->CameraBoom->TargetArmLength == TargetArmLength)
	{
		bShouldTick = false;
	}
}

void UThirdPersonCameraMode::EnterMode(const float& YawRotation)
{
	if (Owner->CurrentCameraMode == Owner->ThirdPersonCameraMode.Get()) return;
	
	TargetRotation = Owner->CurrentCameraMode->TargetRotation;
	Owner->CurrentCameraMode = Owner->ThirdPersonCameraMode.Get();

	bShouldTick = true;
}
