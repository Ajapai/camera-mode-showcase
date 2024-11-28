// Fill out your copyright notice in the Description page of Project Settings.


#include "SideScrollerCameraModeArea.h"
#include "CameraModeShowcase/CameraModeShowcaseCharacter.h"
#include "Components/ArrowComponent.h"

void ASideScrollerCameraModeArea::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ACameraModeShowcaseCharacter::StaticClass()))
	{
		auto Character = Cast<ACameraModeShowcaseCharacter>(OtherActor);
		Character->EnterSideScrollerMode(ArrowComponent->GetComponentRotation().Yaw);
	}
}

void ASideScrollerCameraModeArea::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(ACameraModeShowcaseCharacter::StaticClass()))
	{
		auto Character = Cast<ACameraModeShowcaseCharacter>(OtherActor);
		Character->EnterThirdPersonMode();
	}
}
