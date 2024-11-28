// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownCameraMode.h"

#include "InputActionValue.h"
#include "CameraModeShowcase/CameraModeShowcaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"

void UTopDownCameraMode::HandleLook(const FInputActionValue& Value)
{
}

void UTopDownCameraMode::HandleMove(const FInputActionValue& Value)
{
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

void UTopDownCameraMode::HandleTick(const float& DeltaSeconds)
{
	if (!bShouldTick) return;
	
	Owner->Controller->SetControlRotation(FMath::RInterpTo(Owner->Controller->GetControlRotation(), TargetRotation,
	                                                       DeltaSeconds, 1.5f));
	Owner->CameraBoom->TargetArmLength = FMath::FInterpTo(Owner->CameraBoom->TargetArmLength, TargetArmLength,
	                                                      DeltaSeconds, 1.5f);

	if (Owner->Controller->GetControlRotation() == TargetRotation && Owner->CameraBoom->TargetArmLength == TargetArmLength)
	{
		bShouldTick = false;
	}
}

void UTopDownCameraMode::EnterMode(const float& YawRotation)
{
	Owner->CurrentCameraMode = Owner->TopDownCameraMode.Get();
	TargetRotation = FRotator(270, YawRotation, 0);
	bShouldTick = true;
}
