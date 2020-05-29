// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectTimePauser.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UObjectTimePauser::UObjectTimePauser()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UObjectTimePauser::BeginPlay()
{
	Super::BeginPlay();
	InputComponent = GetWorld() -> GetFirstPlayerController() -> FindComponentByClass<UInputComponent>();
	InputComponent -> BindAction("Time Pause", IE_Pressed, this, &UObjectTimePauser::TimePause).bConsumeInput = false;
	
}


// Called every frame
void UObjectTimePauser::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// When time pause is pressed
	// Call a function which sets the owner of this component to SetSimulatePhysics false.
	// Change material to orange box version

}

void UObjectTimePauser::TimePause()
{
	if (bActive == false)
	{
		bActive = true;
		UPrimitiveComponent* CurrentComponent = GetOwner() -> FindComponentByClass<UPrimitiveComponent>();
		CurrentComponent -> SetSimulatePhysics(false);
		CurrentComponent -> SetMaterial(0, ActiveMaterial);
	}
	else if (bActive == true)
	{
		bActive = false;
		UPrimitiveComponent* CurrentComponent = GetOwner() -> FindComponentByClass<UPrimitiveComponent>();
		CurrentComponent -> SetSimulatePhysics(true);
		CurrentComponent -> SetMaterial(0, NormalMaterial);
	}
}



