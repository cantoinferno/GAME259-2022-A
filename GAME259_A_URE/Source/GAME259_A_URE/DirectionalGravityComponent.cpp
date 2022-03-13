// Fill out your copyright notice in the Description page of Project Settings.


#include "DirectionalGravityComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "GAME259_A_URECharacter.h"

#define M_PI 3.14159265358979323846  /* pi */

// Sets default values for this component's properties
UDirectionalGravityComponent::UDirectionalGravityComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDirectionalGravityComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	Character = Cast<AGAME259_A_URECharacter>(GetOwner());
	Movement = Cast<UCharacterMovementComponent>(Character->GetMovementComponent());
	Movement->GravityScale = 0.0f;
}


// Called every frame
void UDirectionalGravityComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	TargetRotation.Yaw = Character->GetActorRotation().Yaw;
	if(!Movement->IsMovingOnGround()) Movement->Velocity += (Direction * Strength * DeltaTime);

	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Orange, (Direction).ToString());
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Yellow, TargetRotation.ToString());
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Cyan, Character->GetActorRotation().ToString());
	GEngine->AddOnScreenDebugMessage(-1, 0.0f, FColor::Red, Direction.ToOrientationRotator().ToString());
	
	Character->SetActorRotation(FMath::RInterpTo(Character->GetActorRotation(), TargetRotation, DeltaTime, RotationShiftSpeed));
	//GetWorld()->GetFirstPlayerController()->SetControlRotation(FMath::RInterpTo(GetWorld()->GetFirstPlayerController()->GetControlRotation(), TargetRotation, DeltaTime, RotationShiftSpeed));

	if (Character->GetActorRotation() != TargetRotation)
	{
	}
}

void UDirectionalGravityComponent::SetGravity(const FVector& newDirection, float newStrength, FRotator newRotation)
{
	Strength = newStrength;
	Direction = newDirection;
	TargetRotation = newRotation;
	//ControllerRotation = newRotation;
	/*auto tempRotation = Direction.ToOrientationRotator();
	TargetRotation.Pitch = -tempRotation.Pitch;
	TargetRotation.Roll = -tempRotation.Yaw;
	TargetRotation.Yaw = Character->GetActorRotation().Yaw;*/
}

bool UDirectionalGravityComponent::DoJump(bool bReplayingMoves)
{
	if (Character && Character->CanJump())
	{
		float velocityAngle = acos(FVector::DotProduct(Movement->Velocity.GetSafeNormal(), Direction)) - (M_PI / 2);
		FVector upVelocity = Movement->Velocity * sin(velocityAngle);
		if (upVelocity.Size() < Movement->JumpZVelocity)
		{
			Movement->Velocity = (Movement->Velocity * cos(velocityAngle)) + (upVelocity.GetSafeNormal() * Movement->JumpZVelocity);
		}
		Movement->SetMovementMode(MOVE_Falling);
		return true;
	}

	return false;
}

