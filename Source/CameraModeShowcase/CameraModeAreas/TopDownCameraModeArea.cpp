// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownCameraModeArea.h"
#include "CameraModeShowcase/CameraModeShowcaseCharacter.h"
#include "Components/ArrowComponent.h"

void ATopDownCameraModeArea::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->IsA(ACameraModeShowcaseCharacter::StaticClass()))
	{
		const auto Character = Cast<ACameraModeShowcaseCharacter>(OtherActor);
		Character->EnterTopDownMode(ArrowComponent->GetComponentRotation().Yaw);
	}
}

void ATopDownCameraModeArea::OnComponentEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->IsA(ACameraModeShowcaseCharacter::StaticClass()))
	{
		const auto Character = Cast<ACameraModeShowcaseCharacter>(OtherActor);
		Character->LeaveTopDownMode();
	}
}
