// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "ObjectTimePauser.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ALTERNATETIME_API UObjectTimePauser : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectTimePauser();
	void TimePause();
	UPROPERTY(EditAnywhere, BlueprintReadWrite) UMaterialInterface* NormalMaterial;
	UPROPERTY(EditAnywhere, BlueprintReadWrite) UMaterialInterface* ActiveMaterial;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	bool bIsTimePaused = false;
	UInputComponent* InputComponent = nullptr;
	bool bActive = false;

};
