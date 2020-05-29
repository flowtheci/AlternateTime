// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonPressed.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"
#define OUT


// Sets default values for this component's properties
UButtonPressed::UButtonPressed()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UButtonPressed::BeginPlay()
{
	Super::BeginPlay();
	SetupInputComponent();
	PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetPawn();
	InitialLocation = GetOwner() -> GetActorLocation();
	CurrentLocation = InitialLocation;
	InitialHeight = CurrentLocation.Z;
	CurrentHeight = CurrentLocation.Z;
	TargetHeight = InitialHeight - 5.0f;



}


// Called every frame
void UButtonPressed::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	CurrentLocation = GetOwner() -> GetActorLocation();
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (TotalMassOfActors() > 1.f && bTimePaused == false)
	{
		ButtonDown(DeltaTime);
	}
	else if (CurrentHeight != InitialHeight && bTimePaused == false)
	{
		ButtonUp(DeltaTime);
	}
}

void UButtonPressed::ButtonDown(float DeltaTime)
{
	CurrentHeight = FMath::FInterpTo(CurrentHeight, TargetHeight, DeltaTime, ButtonMoveSpeed);
	CurrentLocation.Z = CurrentHeight;
	GetOwner() -> SetActorLocation(CurrentLocation);
}

void UButtonPressed::ButtonUp(float DeltaTime)
{
	CurrentHeight = FMath::FInterpTo(CurrentHeight, InitialHeight, DeltaTime, ButtonMoveSpeed);
	CurrentLocation.Z = CurrentHeight;
	GetOwner() -> SetActorLocation(CurrentLocation);
}

float UButtonPressed::TotalMassOfActors() const
{
	float TotalMass = 0.f;
	// Find all overlapping actors & add up their masses
	TArray<AActor*> OverlappingActors;
	ButtonTrigger -> GetOverlappingActors(OUT OverlappingActors);
	for(AActor* Actor : OverlappingActors)
	{
		TotalMass += Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		if(Actor->GetName() == "BasicCharacterBP_C_0")
		{
			TotalMass += 100.f;
		}
	}
	return TotalMass;
}

void UButtonPressed::SetupInputComponent()
{
	InputComponent = GetWorld() -> GetFirstPlayerController() -> FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Time Pause", IE_Pressed, this, &UButtonPressed::TimePause).bConsumeInput = false;
	}
}

void UButtonPressed::TimePause()
{
	if (bTimePaused == true)
	{
		bTimePaused = false;
	}
	else if (bTimePaused == false)
	{
		bTimePaused = true;
	}
}




