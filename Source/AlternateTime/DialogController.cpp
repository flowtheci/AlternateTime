// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogController.h"
#include "Components/AudioComponent.h"
#define OUT

// Sets default values for this component's properties
UDialogController::UDialogController()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDialogController::BeginPlay()
{
	Super::BeginPlay();
	FindAudioComponents();

	// ...
	
}


// Called every frame
void UDialogController::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CheckForOverlap();
	AudioPlayer();

	// ...
}


void UDialogController::CheckForOverlap()
{	
	Room1Trigger -> GetOverlappingActors(OUT Room1OverlappingActors);
	Room2Trigger -> GetOverlappingActors(OUT Room2OverlappingActors);
	Room3Trigger -> GetOverlappingActors(OUT Room3OverlappingActors);
	Room4Trigger -> GetOverlappingActors(OUT Room4OverlappingActors);
	Room5Trigger -> GetOverlappingActors(OUT Room5OverlappingActors);
	Room6Trigger -> GetOverlappingActors(OUT Room6OverlappingActors);
	FinaleRoomTrigger -> GetOverlappingActors(OUT FinaleRoomOverlappingActors);

	for(AActor* Actor : Room1OverlappingActors)
	{
		if(Actor->GetName() == "BasicCharacterBP_C_0")
		{
			bRoom1Triggered = true;
		}
	}

	for(AActor* Actor : Room2OverlappingActors)
	{
		if(Actor->GetName() == "BasicCharacterBP_C_0")
		{
			bRoom2Triggered = true;
		}
	}

	for(AActor* Actor : Room3OverlappingActors)
	{
		if(Actor->GetName() == "BasicCharacterBP_C_0")
		{
			bRoom3Triggered = true;
		}
	}

	for(AActor* Actor : Room4OverlappingActors)
	{
		if(Actor->GetName() == "BasicCharacterBP_C_0")
		{
			bRoom4Triggered = true;
		}
	}

	for(AActor* Actor : Room5OverlappingActors)
	{
		if(Actor->GetName() == "BasicCharacterBP_C_0")
		{
			bRoom5Triggered = true;
		}
	}

	for(AActor* Actor : Room6OverlappingActors)
	{
		if(Actor->GetName() == "BasicCharacterBP_C_0")
		{
			bRoom6Triggered = true;
		}
	}

	for(AActor* Actor : FinaleRoomOverlappingActors)
	{
		if(Actor->GetName() == "BasicCharacterBP_C_0")
		{
			bFinaleRoomTriggered = true;
		}
	}
}

void UDialogController::FindAudioComponents()
{
	TArray<UAudioComponent*> Comp;
	GetOwner()->GetComponents<UAudioComponent>(Comp);
	if (Comp.Num() < 7)
	{
		UE_LOG(LogTemp, Error, TEXT("%s is missing audio components!"), *GetOwner()->GetName());
	}
	else
	{
		FinaleRoomAudioComponent = Comp[0];
		Room1AudioComponent = Comp[1];
		Room2AudioComponent = Comp[2];
		Room3AudioComponent = Comp[3];
		Room4AudioComponent = Comp[4];
		Room5AudioComponent = Comp[5];
		Room6AudioComponent = Comp[6];
	}
}

void UDialogController::AudioPlayer()
{
	if (bRoom1Triggered && !bRoom1Complete)
	{
		Room1AudioComponent->Stop();
		Room2AudioComponent->Stop();
		Room3AudioComponent->Stop();
		Room4AudioComponent->Stop();
		Room5AudioComponent->Stop();
		Room6AudioComponent->Stop();
		FinaleRoomAudioComponent->Stop();

		Room1AudioComponent->Play();
		bRoom1Complete = true;
	}

	if (bRoom2Triggered && !bRoom2Complete)
	{
		Room1AudioComponent->Stop();
		Room2AudioComponent->Stop();
		Room3AudioComponent->Stop();
		Room4AudioComponent->Stop();
		Room5AudioComponent->Stop();
		Room6AudioComponent->Stop();
		FinaleRoomAudioComponent->Stop();

		Room2AudioComponent->Play();
		bRoom2Complete = true;
	}

	if (bRoom3Triggered && !bRoom3Complete)
	{
		Room1AudioComponent->Stop();
		Room2AudioComponent->Stop();
		Room3AudioComponent->Stop();
		Room4AudioComponent->Stop();
		Room5AudioComponent->Stop();
		Room6AudioComponent->Stop();
		FinaleRoomAudioComponent->Stop();
		
		Room3AudioComponent->Play();
		bRoom3Complete = true;
	}

	if (bRoom4Triggered && !bRoom4Complete)
	{
		Room1AudioComponent->Stop();
		Room2AudioComponent->Stop();
		Room3AudioComponent->Stop();
		Room4AudioComponent->Stop();
		Room5AudioComponent->Stop();
		Room6AudioComponent->Stop();
		FinaleRoomAudioComponent->Stop();

		Room4AudioComponent->Play();
		bRoom4Complete = true;
	}

	if (bRoom5Triggered && !bRoom5Complete)
	{
		Room1AudioComponent->Stop();
		Room2AudioComponent->Stop();
		Room3AudioComponent->Stop();
		Room4AudioComponent->Stop();
		Room5AudioComponent->Stop();
		Room6AudioComponent->Stop();
		FinaleRoomAudioComponent->Stop();
		
		Room5AudioComponent->Play();
		bRoom5Complete = true;
	}

	if (bRoom6Triggered && !bRoom6Complete)
	{
		Room1AudioComponent->Stop();
		Room2AudioComponent->Stop();
		Room3AudioComponent->Stop();
		Room4AudioComponent->Stop();
		Room5AudioComponent->Stop();
		Room6AudioComponent->Stop();
		FinaleRoomAudioComponent->Stop();

		Room6AudioComponent->Play();
		bRoom6Complete = true;
	}

	if (bFinaleRoomTriggered && !bFinaleRoomComplete)
	{
		Room1AudioComponent->Stop();
		Room2AudioComponent->Stop();
		Room3AudioComponent->Stop();
		Room4AudioComponent->Stop();
		Room5AudioComponent->Stop();
		Room6AudioComponent->Stop();
		FinaleRoomAudioComponent->Stop();
		
		FinaleRoomAudioComponent->Play();
		bFinaleRoomComplete = true;
	}
}