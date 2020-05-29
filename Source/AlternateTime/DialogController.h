// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "DialogController.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ALTERNATETIME_API UDialogController : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDialogController();
	void CheckForOverlap();
	void FindAudioComponents();
	void AudioPlayer();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(EditAnywhere) ATriggerVolume* Room1Trigger;
	UPROPERTY(EditAnywhere) ATriggerVolume* Room2Trigger;
	UPROPERTY(EditAnywhere) ATriggerVolume* Room3Trigger;
	UPROPERTY(EditAnywhere) ATriggerVolume* Room4Trigger;
	UPROPERTY(EditAnywhere) ATriggerVolume* Room5Trigger;
	UPROPERTY(EditAnywhere) ATriggerVolume* Room6Trigger;
	UPROPERTY(EditAnywhere) ATriggerVolume* FinaleRoomTrigger;

	TArray<AActor*> Room1OverlappingActors;
	TArray<AActor*> Room2OverlappingActors;
	TArray<AActor*> Room3OverlappingActors;
	TArray<AActor*> Room4OverlappingActors;
	TArray<AActor*> Room5OverlappingActors;
	TArray<AActor*> Room6OverlappingActors;
	TArray<AActor*> FinaleRoomOverlappingActors;

	bool bRoom1Triggered = false;
	bool bRoom2Triggered = false;
	bool bRoom3Triggered = false;
	bool bRoom4Triggered = false;
	bool bRoom5Triggered = false;
	bool bRoom6Triggered = false;
	bool bFinaleRoomTriggered = false;

	UPROPERTY() UAudioComponent* Room1AudioComponent = nullptr;
	UPROPERTY() UAudioComponent* Room2AudioComponent = nullptr;
	UPROPERTY() UAudioComponent* Room3AudioComponent = nullptr;
	UPROPERTY() UAudioComponent* Room4AudioComponent = nullptr;
	UPROPERTY() UAudioComponent* Room5AudioComponent = nullptr;
	UPROPERTY() UAudioComponent* Room6AudioComponent = nullptr;
	UPROPERTY() UAudioComponent* FinaleRoomAudioComponent = nullptr;

	bool bRoom1Complete = false;
	bool bRoom2Complete = false;
	bool bRoom3Complete = false;
	bool bRoom4Complete = false;
	bool bRoom5Complete = false;
	bool bRoom6Complete = false;
	bool bFinaleRoomComplete = false;
		
};
