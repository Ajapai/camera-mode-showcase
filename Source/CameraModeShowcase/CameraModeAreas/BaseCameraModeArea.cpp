// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCameraModeArea.h"

#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"

ABaseCameraModeArea::ABaseCameraModeArea()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(FName("BoxCollider"));
	RootComponent = BoxCollider;

	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(FName("ArrowComponent"));
	ArrowComponent->SetupAttachment(BoxCollider);

	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ABaseCameraModeArea::OnComponentBeginOverlap);
	BoxCollider->OnComponentEndOverlap.AddDynamic(this, &ABaseCameraModeArea::OnComponentEndOverlap);
}
