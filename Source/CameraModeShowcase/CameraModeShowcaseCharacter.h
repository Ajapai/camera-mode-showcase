// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CameraModes/TopDownCameraMode.h"
#include "CameraModes/ThirdPersonCameraMode.h"
#include "CameraModes/SideScrollerCameraMode.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "CameraModeShowcaseCharacter.generated.h"

class UBaseCameraMode;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class USpringArmComponent;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class ACameraModeShowcaseCharacter : public ACharacter
{
	GENERATED_BODY()


	// Initializers
public:
	ACameraModeShowcaseCharacter();


	// Overrides
public:
	virtual void Tick(float DeltaSeconds) override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
protected:
	virtual void NotifyControllerChanged() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	

	// UProperties
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom|Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom|Camera", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom|Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom|Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom|Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Custom|Input", meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;
	

	// Member Functions
public:
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	void EnterSideScrollerMode(const float& YawRotation);
	void LeaveSideScrollerMode();
	void EnterTopDownMode(const float& YawRotation);
	void LeaveTopDownMode();
	
protected:
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);


	// Member Pointers
private:
	TWeakObjectPtr<UBaseCameraMode> CurrentCameraMode;
	TStrongObjectPtr<USideScrollerCameraMode> SideScrollerCameraMode;
	TStrongObjectPtr<UThirdPersonCameraMode> ThirdPersonCameraMode;
	TStrongObjectPtr<UTopDownCameraMode> TopDownCameraMode;


	// Member Variables
private:
	bool bCurrentlyInSideScrollerCollider = false;
	bool bCurrentlyInTopDownCollider = false;
	float CurrentSideScrollerYaw = 0;
	float CurrentTopDownYaw = 0;


	// Friend Classes
public:
	friend class USideScrollerCameraMode;
	friend class UThirdPersonCameraMode;
	friend class UTopDownCameraMode;
};

