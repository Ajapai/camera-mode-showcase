// Fill out your copyright notice in the Description page of Project Settings.


#include "SideScrollerCameraMode.h"

#include "InputActionValue.h"
#include "CameraModeShowcase/CameraModeShowcaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"

void USideScrollerCameraMode::HandleLook(const FInputActionValue& Value)
{}

void USideScrollerCameraMode::HandleMove(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Owner->Controller != nullptr)
	{
		const FRotator YawRotation(0, TargetRotation.Yaw, 0);

		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		Owner->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void USideScrollerCameraMode::HandleTick(const float& DeltaSeconds)
{
	Owner->Controller->SetControlRotation(FMath::RInterpTo(Owner->Controller->GetControlRotation(), TargetRotation,
	                                                       DeltaSeconds, 1.5f));
	Owner->CameraBoom->TargetArmLength = FMath::FInterpTo(Owner->CameraBoom->TargetArmLength, TargetArmLength,
	                                                      DeltaSeconds, 1.5f);
}

void USideScrollerCameraMode::EnterMode(const float& YawRotation)
{
	Owner->CurrentCameraMode = Owner->SideScrollerCameraMode.Get();
	TargetRotation = FRotator(0, YawRotation, 0);
}
