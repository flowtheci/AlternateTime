// Fill out your copyright notice in the Description page of Project Settings.


#include "LightOn.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"
#define OUT


// Sets default values for this component's properties
ULightOn::ULightOn()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULightOn::BeginPlay()
{
	Super::BeginPlay();
	InitialRotation = GetOwner() -> GetActorRotation();
	InitialYaw = InitialRotation.Yaw;
	TargetYaw = InitialYaw + 180.0f;
	TargetRotation = InitialRotation;
	TargetRotation.Yaw = TargetYaw;
	PlayerCharacter = GetWorld() -> GetFirstPlayerController() -> GetPawn();

}


// Called every frame
void ULightOn::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (LightActivator && TotalMassOfActors() > 1.f)
	{
		GetOwner() -> SetActorRotation(TargetRotation);
	}
	else if (GetOwner() -> GetActorRotation().Yaw != InitialYaw)
	{
		GetOwner() -> SetActorRotation(InitialRotation);
	}

}

float ULightOn::TotalMassOfActors() const
{
	float TotalMass = 0.f;
	// Find all overlapping actors & add up their masses
	TArray<AActor*> OverlappingActors;
	LightActivator -> GetOverlappingActors(OUT OverlappingActors);
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





