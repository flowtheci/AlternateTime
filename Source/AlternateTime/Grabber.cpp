// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "DrawDebugHelpers.h"


#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	SetupInputComponent();
	FindPhysicsHandle();

}

void UGrabber::TimePauseToggle()
{
	bAntiTimeComponentFound = false;
	bTimeComponentFound = false;
	if (bIfTimeIsPaused == false)
	{
		bIfTimeIsPaused = true;
		if (bIsGrabbed == true)
		{

				TArray<UActorComponent*> ATComponentsList = PhysicsHandle->GetGrabbedComponent()->GetOwner()->GetComponentsByTag(UStaticMeshComponent::StaticClass(), "AntiTime");
				if(ATComponentsList.Num() != 0)
				{
					AntiTimeComponent = ATComponentsList[0];
					bAntiTimeComponentFound = true;
					bTimeComponentFound = false;
				}

				TArray<UActorComponent*> TComponentsList = PhysicsHandle->GetGrabbedComponent()->GetOwner()->GetComponentsByTag(UStaticMeshComponent::StaticClass(), "Time");
				if(TComponentsList.Num() != 0)
				{
					TimeComponent = TComponentsList[0];
					bAntiTimeComponentFound = false;
					bTimeComponentFound = true;
				}
			
			if (bAntiTimeComponentFound == true)
			{
				if(PhysicsHandle->GetGrabbedComponent() == AntiTimeComponent->GetOwner()->FindComponentByClass<UPrimitiveComponent>())
				{
					// What to do when the held item is anti time
					bHeldObjectIsAntiTime = true;
				}
				
			}
			else if (bTimeComponentFound == true)
			{
				if(PhysicsHandle->GetGrabbedComponent() == TimeComponent->GetOwner()->FindComponentByClass<UPrimitiveComponent>())
				{
					// What to do when the held item is a normal box
					PhysicsHandle->GetGrabbedComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
					PhysicsHandle->ReleaseComponent();
					bHeldObjectIsAntiTime = false;
					bIsGrabbed = false;
				}

			}

		}
		
	}

	else if (bIfTimeIsPaused)
	{
		bIfTimeIsPaused = false;
	}
	
}


void UGrabber::Grab()
{
	// When item is not grabbed & if the time is not paused
	if ((bIsGrabbed == false && bIfTimeIsPaused == false) || (bIsGrabbed == false && bIfTimeIsPaused == true && bHeldObjectIsAntiTime == true))
	{	
		FHitResult HitResult = GetObjectInReach();
		UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

		// Pick up physics based object in raytrace if object found
		if (HitResult.GetActor())
		{
			PhysicsHandle->GrabComponentAtLocationWithRotation(ComponentToGrab, NAME_None, LineTraceEnd, PlayerViewRotation);
			bIsGrabbed = true;
			UE_LOG(LogTemp, Warning, TEXT("Grabber used!"));
			PhysicsHandle->GetGrabbedComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Grabber used, but no suitable object found!"));
			bIsGrabbed = false;
		}
	}

	// When object is already grabbed but time is not paused & object is not an anti time box
	else if ((bIsGrabbed == true && bIfTimeIsPaused == false)  || (bIsGrabbed == true && bIfTimeIsPaused == true && bHeldObjectIsAntiTime == true))
	{
		UE_LOG(LogTemp, Warning, TEXT("Grabber released!"));
		PhysicsHandle->SetTargetLocationAndRotation(PlayerViewLocation, PlayerViewRotation);
		PhysicsHandle->GetGrabbedComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
		PhysicsHandle->ReleaseComponent();
		bIsGrabbed = false;
		bHeldObjectIsAntiTime = false;
		bAntiTimeComponentFound = false;
		bTimeComponentFound = true;
		
	}

	else if (bIfTimeIsPaused == true && bIsGrabbed == false)
	{
		FHitResult HitResult = GetObjectInReach();
		UPrimitiveComponent* ComponentToGrab = HitResult.GetComponent();

		// Pick up physics based object in raytrace if object found
		if (HitResult.GetActor())
		{
			if(!CheckIfObjectObeyTime(ComponentToGrab))
			{
				PhysicsHandle->GrabComponentAtLocationWithRotation(ComponentToGrab, NAME_None, LineTraceEnd, PlayerViewRotation);
				bIsGrabbed = true;
				UE_LOG(LogTemp, Warning, TEXT("Grabber used!"));
				PhysicsHandle->GetGrabbedComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
			}
			else
			{
				UE_LOG(LogTemp, Error, TEXT("Grabber cannot be used on normal boxes during Time Pause!"));
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Grabber used, but no suitable object found!"));
			bIsGrabbed = false;
		}
	}
}


void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (PhysicsHandle->GrabbedComponent)
	{
		FindNewLineTraceEnd();
		PhysicsHandle->SetTargetLocationAndRotation(LineTraceEnd, PlayerViewRotation);
	} 

	//bool bIsTimePausePressed = PlayerController->WasInputKeyJustPressed(FKey ("F"));
	//if (bIsTimePausePressed)
	//{
	//	TimePauseToggle();
	//}

	// FindNewLineTraceEnd(); DrawDebugLine(GetWorld(), PlayerViewLocation, LineTraceEnd, FColor(0, 255, 0), false, 0.f, 0, 5.f); // Draw debug line which shows raycast line
}

void UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner() -> FindComponentByClass<UPhysicsHandleComponent>();
	if (PhysicsHandle) {}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Object %s has no PhysicsHandle component attached!"), *GetOwner() -> GetName());
	}
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner() -> FindComponentByClass<UInputComponent>();
	InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	InputComponent->BindAction("Time Pause", IE_Pressed, this, &UGrabber::TimePauseToggle).bConsumeInput = false;
}

FHitResult UGrabber::GetObjectInReach()
{
	FindNewLineTraceEnd();
	// Calculate the raytrace
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	GetWorld() -> LineTraceSingleByObjectType(OUT Hit, PlayerViewLocation, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParams);

	// If raycast hits an actor.
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Raycast hit actor %s!"), *ActorHit -> GetName());
	}

	return Hit;
}

void UGrabber::FindNewLineTraceEnd()
{
	// Get player view coordinates and rotation.
	GetWorld() -> GetFirstPlayerController() -> GetPlayerViewPoint(OUT PlayerViewLocation, OUT PlayerViewRotation);

	// Calculate where raycast should end using the Reach float
	LineTraceEnd = PlayerViewLocation + PlayerViewRotation.Vector() * Reach; 
}


bool UGrabber::CheckIfObjectObeyTime(UPrimitiveComponent *CheckedObject)
{
	TArray<UActorComponent*> ATComponentsList = CheckedObject->GetOwner()->GetComponentsByTag(UStaticMeshComponent::StaticClass(), "AntiTime");
	if(ATComponentsList.Num() != 0)
	{
		AntiTimeComponent = ATComponentsList[0];
		bHeldObjectIsAntiTime = true;
		return false;
	}

	TArray<UActorComponent*> TComponentsList = CheckedObject->GetOwner()->GetComponentsByTag(UStaticMeshComponent::StaticClass(), "Time");
	if(TComponentsList.Num() != 0)
	{
		TimeComponent = TComponentsList[0];
		bHeldObjectIsAntiTime = false;
		return true;
	}
	return true;		
} 


