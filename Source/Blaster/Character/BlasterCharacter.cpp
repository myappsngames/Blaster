// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ABlasterCharacter::ABlasterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->bUsePawnControlRotation = true; // rotate CameraBoom along with controller when adding mouse input

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

}

// Called when the game starts or when spawned
void ABlasterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ABlasterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Bind Characters inherited Jump Function directly
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);

	// Bind Movement functions to inputs
	PlayerInputComponent->BindAxis("MoveForward", this, &ABlasterCharacter::MoveForward); // this: this character; the user object
	PlayerInputComponent->BindAxis("MoveRight", this, &ABlasterCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ABlasterCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ABlasterCharacter::LookUp);
}

void ABlasterCharacter::MoveForward(float Value)
{
	if (Controller != nullptr && Value != 0.f)
	{
		// declare local variable named YawRotation
		const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f); // 0 for pitch and roll; parallel to the ground
		// Create FRotationMatrix from FRotator, and Call GetUnitAxis to return an FVector
		const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X)); // FVector represents direction of Yaw rotation
		AddMovementInput(Direction, Value);
	}
}

void ABlasterCharacter::MoveRight(float Value)
{
	const FRotator YawRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);
	// Get Y Axis from Yaw Rotation Matrix
	const FVector Direction(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y)); 
	AddMovementInput(Direction, Value);
}

void ABlasterCharacter::Turn(float Value)
{
	// Add Yaw to Controller Rotation
	AddControllerYawInput(Value); // Value represents how fast mouse is being moved left and right
}

void ABlasterCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}


// Called every frame
void ABlasterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



