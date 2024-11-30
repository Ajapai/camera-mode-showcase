// Fill out your copyright notice in the Description page of Project Settings.


#include "ThirdPersonCameraMode.h"

#include "InputActionValue.h"
#include "CameraModeShowcase/CameraModeShowcaseCharacter.h"
#include "GameFramework/SpringArmComponent.h"

void UThirdPersonCameraMode::HandleLook(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Owner->Controller != nullptr)
	{
		Owner->AddControllerYawInput(LookAxisVector.X);
		Owner->AddControllerPitchInput(LookAxisVector.Y);
		if (LookAxisVector.Y < 0.001f || LookAxisVector.Y > -0.001f)
		{
			bShouldInterpolateRotation = false;
		}
	}
}

void UThirdPersonCameraMode::HandleMove(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Owner->Controller != nullptr)
	{
		const FRotator Rotation = Owner->Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		Owner->AddMovementInput(ForwardDirection, MovementVector.Y);
		Owner->AddMovementInput(RightDirection, MovementVector.X);
	}
}

void UThirdPersonCameraMode::HandleTick(const float& DeltaSeconds)
{
	Owner->CameraBoom->TargetArmLength = FMath::FInterpTo(Owner->CameraBoom->TargetArmLength, TargetArmLength,
													  DeltaSeconds, 1.5f);
	
	if (!bShouldInterpolateRotation) return;

	auto OwnerRotation = Owner->Controller->GetControlRotation();
	
	Owner->Controller->SetControlRotation(FMath::RInterpTo(OwnerRotation, FRotator(TargetRotation.Pitch, OwnerRotation.Yaw, OwnerRotation.Roll),
													   DeltaSeconds, 1.5f));
}

void UThirdPersonCameraMode::EnterMode(const float& YawRotation)
{
	if (Owner->CurrentCameraMode == Owner->ThirdPersonCameraMode.Get()) return;
	
	TargetRotation = FRotator(315, Owner->CurrentCameraMode->TargetRotation.Yaw, 0);
	
	Owner->CurrentCameraMode = Owner->ThirdPersonCameraMode.Get();

	bShouldInterpolateRotation = true;

	Owner->CameraBoom->bDoCollisionTest = true;
}
