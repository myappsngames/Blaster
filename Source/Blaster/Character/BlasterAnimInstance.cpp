// Fill out your copyright notice in the Description page of Project Settings.


#include "BlasterAnimInstance.h"
#include "BlasterCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UBlasterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	// set BlasterCharacter to result of TryGetPawnOwner
	BlasterCharacter = Cast<ABlasterCharacter>(TryGetPawnOwner());
}

void UBlasterAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	// Make sure BlasterCharacter is accessed only after being set
	if (BlasterCharacter == nullptr)
	{
		BlasterCharacter = Cast<ABlasterCharacter>(TryGetPawnOwner());
	}
	if (BlasterCharacter == nullptr) return;

	// Get Velocity
	FVector Velocity = BlasterCharacter->GetVelocity();
	Velocity.Z = 0.f; // Only want lateral speed; do not want Z component
	// Set Speed
	Speed = Velocity.Size(); // size of vector
	
	// Set bIsInAir; Get Character's movement component from GameFramework/CharacterMovementComponent.h
	bIsInAir = BlasterCharacter->GetCharacterMovement()->IsFalling(); // if falling, BIsInAir is set to true

	// Set bIsAccelerating; // if size of current acceleration is > 0 then true, otherwise false
	bIsAccelerating = BlasterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f ? true : false; 

}