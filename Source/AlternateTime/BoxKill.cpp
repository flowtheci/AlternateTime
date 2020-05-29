// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxKill.h"
#include "Engine/World.h"
#define OUT

// Sets default values for this component's properties
UBoxKill::UBoxKill()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBoxKill::BeginPlay()
{
	Super::BeginPlay();
	AActor* PlayerCharacter = GetWorld()->GetFirstPlayerController()->GetPawn();

	// ...
	
}


// Called every frame
void UBoxKill::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	DestroyOnOverlap();
}

void UBoxKill::DestroyOnOverlap()
{
	TArray<AActor*> OverlappingActors;
	BoxKillTrigger -> GetOverlappingActors(OUT OverlappingActors);
	if(OverlappingActors.Num() > 0)
	{
		for(AActor* Actor : OverlappingActors)
		{
			UE_LOG(LogTemp, Warning, TEXT("Actor in triggervolume: %s"), *Actor->GetName());
			if(Actor->GetName() != "BasicCharacterBP_C_0")
			{
				Actor->Destroy();
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Actor destroy stopped as it is player character."));
			}
		}	
	}
}


