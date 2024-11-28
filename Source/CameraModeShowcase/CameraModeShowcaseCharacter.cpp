// Copyright Epic Games, Inc. All Rights Reserved.

#include "CameraModeShowcaseCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

//////////////////////////////////////////////////////////////////////////
// ACameraModeShowcaseCharacter

ACameraModeShowcaseCharacter::ACameraModeShowcaseCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Note: For faster iteration times these variables, and many more, can be tweaked in the Character Blueprint
	// instead of recompiling to adjust them
	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create Camera Modes
	SideScrollerCameraMode = TStrongObjectPtr(CreateDefaultSubobject<USideScrollerCameraMode>(FName("SideScrollerCameraMode")));
	SideScrollerCameraMode->Owner = this;
	
	ThirdPersonCameraMode = TStrongObjectPtr(CreateDefaultSubobject<UThirdPersonCameraMode>(FName("ThirdPersonCameraMode")));
	ThirdPersonCameraMode->Owner = this;
	
	TopDownCameraMode = TStrongObjectPtr(CreateDefaultSubobject<UTopDownCameraMode>(FName("TopDownCameraMode")));
	TopDownCameraMode->Owner = this;

	CurrentCameraMode = ThirdPersonCameraMode.Get();
}

void ACameraModeShowcaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	CurrentCameraMode->HandleTick(DeltaSeconds);
}

void ACameraModeShowcaseCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	SideScrollerCameraMode.Reset();
	ThirdPersonCameraMode.Reset();
	TopDownCameraMode.Reset();
}

//////////////////////////////////////////////////////////////////////////
// Input

void ACameraModeShowcaseCharacter::NotifyControllerChanged()
{
	Super::NotifyControllerChanged();

	// Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ACameraModeShowcaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACameraModeShowcaseCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACameraModeShowcaseCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void ACameraModeShowcaseCharacter::EnterSideScrollerMode(const float& YawRotation) const
{
	SideScrollerCameraMode->EnterMode(YawRotation);
}

void ACameraModeShowcaseCharacter::EnterThirdPersonMode() const
{
	ThirdPersonCameraMode->EnterMode();
}

void ACameraModeShowcaseCharacter::EnterTopDownMode(const float& YawRotation) const
{
	TopDownCameraMode->EnterMode(YawRotation);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ACameraModeShowcaseCharacter::Move(const FInputActionValue& Value)
{
	CurrentCameraMode->HandleMove(Value);
}

// ReSharper disable once CppMemberFunctionMayBeConst
void ACameraModeShowcaseCharacter::Look(const FInputActionValue& Value)
{
	CurrentCameraMode->HandleLook(Value);
}
