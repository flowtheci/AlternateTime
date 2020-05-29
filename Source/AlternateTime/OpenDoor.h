// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ALTERNATETIME_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float TotalMassOfActors() const;
	float TotalMassOfActorsAndGate() const;
	void SetupInputComponent();	
	void TimePause();
	void FindAudioComponent();
	void FinalTimer();
	void FinalButton();

	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	void TutorialTimer();
	void TutorialTimer2();
	UPROPERTY(EditAnywhere) float LoopTime;
	UPROPERTY() FTimerHandle TimerHandle;

private:

	FVector InitialLocation;
	float InitialCoord;
	float TargetCoord;
	FRotator InitialRotation;
	FRotator CurrentRotation;
	float InitialRoll;
	float TargetRoll;
	float CurrentRoll;
	UPROPERTY(EditAnywhere) float OpenDistance = 250.f;
	FVector TargetLocation;
	FVector CurrentLocation;
	float CurrentCoord;
	UPROPERTY(EditAnywhere) ATriggerVolume* DoorTrigger;
	UPROPERTY(EditAnywhere) ATriggerVolume* DoorTrigger2;
	UPROPERTY(EditAnywhere) float DoorOpenSpeed = 2.0f;
	UPROPERTY(EditAnywhere) float DoorCloseSpeed = 4.0f;
	UInputComponent* InputComponent = nullptr;
	bool bTimePaused = false;
	UPROPERTY(EditAnywhere) bool bIsAndGate = false;
	UPROPERTY() UAudioComponent* OpenAudioComponent = nullptr;
	UPROPERTY() UAudioComponent* CloseAudioComponent = nullptr;
	bool bSoundPlayedOpen = false;
	bool bSoundPlayedClosed = false;
	bool bAudioComponent = false;
	UPROPERTY(EditAnywhere) bool bMoveByRotation = false;
	UPROPERTY(EditAnywhere) bool bMoveByX = false;
	UPROPERTY(EditAnywhere) bool bFirstLevelDoor = false;
	UPROPERTY(EditAnywhere) bool bDontCloseDoor = false;
	bool bTutorialOver = false;
	bool bOpenTriggered = false;
	UPROPERTY(EditAnywhere) bool bConstantlyMoving = false;
	bool bTimerOver = false;
	bool bLoopDoor = false;
	UPROPERTY(EditAnywhere) bool bFinalButton = false;
	bool bGameOver = false;




		
};
