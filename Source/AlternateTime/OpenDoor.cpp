// Fill out your copyright notice in the Description page of Project Settings.


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"
#include "Components/AudioComponent.h"
#include "GameFramework/PlayerController.h"
#include "Components/PrimitiveComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GenericPlatform/GenericPlatformProcess.h"
#define OUT

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	SetupInputComponent();
	FindAudioComponent();

	if (bFinalButton)
	{
		return;
	}
	if (bConstantlyMoving)
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UOpenDoor::TutorialTimer, LoopTime, true);
		InitialLocation = GetOwner() -> GetActorLocation();
		CurrentLocation = InitialLocation;
		InitialCoord = InitialLocation.Z;
		CurrentCoord = InitialCoord;
		TargetCoord = InitialCoord + OpenDistance;
		return;
	}

	if (bFirstLevelDoor)
	{
		InitialLocation = GetOwner() -> GetActorLocation();
		CurrentLocation = InitialLocation;
		InitialCoord = InitialLocation.Z;
		CurrentCoord = InitialCoord;
		TargetCoord = InitialCoord + OpenDistance;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UOpenDoor::TutorialTimer, LoopTime, true);
	}

	if(bMoveByX == false)
	{
		InitialLocation = GetOwner() -> GetActorLocation();
		CurrentLocation = InitialLocation;
		InitialCoord = InitialLocation.Z;
		CurrentCoord = InitialCoord;
		TargetCoord = InitialCoord + OpenDistance;
	}


	if (!DoorTrigger)
	{
		UE_LOG(LogTemp, Error, TEXT("Actor %s has the open door component on it, but no DoorTrigger set!"), *GetOwner()->GetName());
	}
	
	if(bIsAndGate && !DoorTrigger2)
	{
		UE_LOG(LogTemp, Error, TEXT("Actor %s is an AND gate, but no second DoorTrigger set!"), *GetOwner()->GetName());
	}

	if (bMoveByRotation)
	{
		InitialRotation = GetOwner()->GetActorRotation();
		CurrentRotation = InitialRotation;
		InitialRoll = InitialRotation.Roll;
		CurrentRoll = InitialRoll;
		TargetRoll = InitialRoll + OpenDistance;
	}

	if (bMoveByX)
	{
		InitialLocation = GetOwner()->GetActorLocation();
		CurrentLocation = InitialLocation;
		InitialCoord = InitialLocation.X;
		CurrentCoord = InitialCoord;
		TargetCoord = InitialCoord + OpenDistance;
	}
}

void UOpenDoor::FindAudioComponent()
{
	TArray<UAudioComponent*> Comp;
	GetOwner()->GetComponents<UAudioComponent>(Comp);
	if (Comp.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("%s is missing audio components!"), *GetOwner()->GetName());
		bAudioComponent = false;
	}
	else
	{
		OpenAudioComponent = Comp[0];
		CloseAudioComponent = Comp[1];
		bAudioComponent = true;
	}


}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (bFinalButton)
	{
		if (TotalMassOfActors() > 1.f && bTimePaused == false)
		{
			UGameplayStatics::OpenLevel(this, "MainMenu");
			UE_LOG(LogTemp, Warning, TEXT("Exiting game..."));
		}
	}
	if (bConstantlyMoving)
	{
		if (bLoopDoor)
		{
			OpenDoor(DeltaTime);
			bTutorialOver = false;
		}
		else if (!bLoopDoor)
		{
			CloseDoor(DeltaTime);
			bTutorialOver = false;
			bTimerOver = false;
		}
		return;
	}
	if(bTutorialOver == true)
	{
		OpenDoor(DeltaTime);
		return;
	}
	if (bIsAndGate == false && bFirstLevelDoor == false)
	{
		if (TotalMassOfActors() > 1.f && bTimePaused == false)
		{
			OpenDoor(DeltaTime);
		}
		else if (bMoveByRotation == false && CurrentCoord != InitialCoord && bTimePaused == false && bDontCloseDoor == false)
		{
			CloseDoor(DeltaTime);
		}
		else if (bMoveByRotation == true && CurrentRoll != InitialRoll && bTimePaused == false && bDontCloseDoor == false)
		{
			CloseDoor(DeltaTime);
		}
	}

	else
	{
		if(TotalMassOfActors() > 1.f && TotalMassOfActorsAndGate() > 1.f && bTimePaused == false && bFirstLevelDoor == false)
		{
			OpenDoor(DeltaTime);
		}
		else if (CurrentCoord != InitialCoord && bTimePaused == false && bDontCloseDoor == false)
		{
			CloseDoor(DeltaTime);
		}
		
	}

	if (bOpenTriggered)
	{
		OpenDoor(DeltaTime);
	}
	// ...
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	bSoundPlayedClosed = false;

	if(bMoveByRotation == false && bDontCloseDoor == false)
	{
		CurrentCoord = FMath::FInterpTo(CurrentCoord, TargetCoord, DeltaTime, DoorOpenSpeed);
		if (bMoveByX)
		{
			CurrentLocation.X = CurrentCoord;
		}
		else
		{
			CurrentLocation.Z = CurrentCoord;
		}
		GetOwner() -> SetActorLocation(CurrentLocation);		
	}

	else if (bDontCloseDoor == true && bMoveByRotation == false)
	{
		CurrentCoord = FMath::FInterpTo(CurrentCoord, TargetCoord, DeltaTime, DoorOpenSpeed);
		if (bMoveByX)
		{
			CurrentLocation.X = CurrentCoord;
		}
		else
		{
			CurrentLocation.Z = CurrentCoord;
		}
		GetOwner() -> SetActorLocation(CurrentLocation);
		bOpenTriggered = true;
	}

	else
	{
		CurrentRoll = FMath::FInterpTo(CurrentRoll, TargetRoll, DeltaTime, DoorOpenSpeed);
		CurrentRotation.Roll = CurrentRoll;
		GetOwner() -> SetActorRotation(CurrentRotation);
	}
	

	if(!bSoundPlayedOpen && bAudioComponent == true)
		{
			OpenAudioComponent->Play();
		}

	bSoundPlayedOpen = true;
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	bSoundPlayedOpen = false;
	if(!bMoveByRotation)
	{
		CurrentCoord = FMath::FInterpTo(CurrentCoord, InitialCoord, DeltaTime, DoorCloseSpeed);
		if (bMoveByX)
		{
			CurrentLocation.X = CurrentCoord;
		}
		else
		{
			CurrentLocation.Z = CurrentCoord;
		}
		
		GetOwner() -> SetActorLocation(CurrentLocation);		
	}

	if (bMoveByRotation)
	{
		CurrentRoll = FMath::FInterpTo(CurrentRoll, InitialRoll, DeltaTime, DoorCloseSpeed);
		CurrentRotation.Roll = CurrentRoll;
		GetOwner() -> SetActorRotation(CurrentRotation);	
	}
	


	if(!bSoundPlayedClosed && bAudioComponent == true)
	{
		CloseAudioComponent->Play();
	}

	bSoundPlayedClosed = true;

}

float UOpenDoor::TotalMassOfActors() const
{
	float TotalMass = 0.f;
	// Find all overlapping actors & add up their masses
	TArray<AActor*> OverlappingActors;
	DoorTrigger -> GetOverlappingActors(OUT OverlappingActors);
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

float UOpenDoor::TotalMassOfActorsAndGate() const
{
	float TotalMass = 0.f;
	// Find all overlapping actors & add up their masses
	TArray<AActor*> OverlappingActors;
	DoorTrigger2 -> GetOverlappingActors(OUT OverlappingActors);
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

void UOpenDoor::SetupInputComponent()
{
	InputComponent = GetWorld() -> GetFirstPlayerController() -> FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Time Pause", IE_Pressed, this, &UOpenDoor::TimePause).bConsumeInput = false;
	}
}

void UOpenDoor::TimePause()
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

void UOpenDoor::TutorialTimer()
{
	bTutorialOver = true;
	bLoopDoor = true;
	if(bConstantlyMoving)
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UOpenDoor::TutorialTimer2, LoopTime, true);
	}
}

void UOpenDoor::TutorialTimer2()
{
	bLoopDoor = false;
	if(bConstantlyMoving)
	{
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UOpenDoor::TutorialTimer, LoopTime, true);
	}
}
