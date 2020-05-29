// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "ButtonPressed.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ALTERNATETIME_API UButtonPressed : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UButtonPressed();
	void ButtonDown(float DeltaTime);
	void ButtonUp(float DeltaTime);
	float TotalMassOfActors() const;
	void SetupInputComponent();	
	void TimePause();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(EditAnywhere) ATriggerVolume* ButtonTrigger;
	UPROPERTY(EditAnywhere) AActor* PlayerCharacter;
	UPROPERTY(EditAnywhere) float ButtonMoveSpeed = 1.0f;
	FVector InitialLocation;
	FVector CurrentLocation;
	float CurrentHeight;
	float TargetHeight;
	float InitialHeight;
	UInputComponent* InputComponent = nullptr;
	bool bTimePaused = false;
		
};
