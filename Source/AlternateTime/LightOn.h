// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "LightOn.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ALTERNATETIME_API ULightOn : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULightOn();
	void ButtonTurnGreen();
	void ButtonTurnRed();
	float TotalMassOfActors() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	FRotator InitialRotation;
	FRotator TargetRotation;
	float InitialYaw;
	float TargetYaw;
	UPROPERTY(EditAnywhere) ATriggerVolume* LightActivator;
	UPROPERTY(EditAnywhere) AActor* PlayerCharacter;


};
