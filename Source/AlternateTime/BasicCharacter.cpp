// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicCharacter.h"
#include "GameFramework/Character.h"

// Sets default values
ABasicCharacter::ABasicCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	CameraComponent -> SetupAttachment(GetCapsuleComponent());
	CameraComponent -> RelativeLocation = FVector(-40.f, 1.7f, 50.f);
	CameraComponent -> bUsePawnControlRotation = true;



}

// Called when the game starts or when spawned
void ABasicCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABasicCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ABasicCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Forward", this, &ABasicCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Right", this, &ABasicCharacter::MoveRight);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);	

	// Mouse axis bind
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABasicCharacter::MoveForward(float Val)
{
	if(Val!=0)
	{
		AddMovementInput(GetActorForwardVector(), Val);
	}
}

void ABasicCharacter::MoveRight(float Val)
{
	if(Val!=0)
	{
		AddMovementInput(GetActorRightVector(), Val);
	}
}

