
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ALTERNATETIME_API UGrabber : public UActorComponent
{
	GENERATED_BODY()


public:	
	// Sets default values for this component's properties
	UGrabber();
	void Grab();
	void TimePauseToggle();
	void FindPhysicsHandle();
	void SetupInputComponent();	
	FHitResult GetObjectInReach();
	void FindNewLineTraceEnd();
	bool CheckIfObjectObeyTime(UPrimitiveComponent*);
	


	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere) float Reach = 210.f;
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;
	FVector LineTraceEnd;
	FVector PlayerViewLocation;
	FRotator PlayerViewRotation;
	FHitResult Hit;
	bool bIsGrabbed = false;
	bool bIfTimeIsPaused = false;
	FVector ObjectLocationOnPause;
	FRotator ObjectRotationOnPause;
	UPrimitiveComponent *HeldComponent;
	UPROPERTY(EditAnywhere) UMaterialInterface* NormalMaterial;
	UPROPERTY(EditAnywhere) UMaterialInterface* ActiveMaterial;
	UActorComponent* AntiTimeComponent;
	UActorComponent* TimeComponent;
	bool bAntiTimeComponentFound = false;
	bool bTimeComponentFound = false;
	bool bHeldObjectIsAntiTime = false;
	bool bNothingFound = true;
};
