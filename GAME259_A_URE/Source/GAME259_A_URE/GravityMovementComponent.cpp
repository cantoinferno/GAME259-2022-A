// Fill out your copyright notice in the Description page of Project Settings.

#include "GravityMovementComponent.h"
#include "GameFramework/Character.h"

#define M_PI 3.14159265358979323846  /* pi */

bool UGravityMovementComponent::DoJump(bool bReplayingMoves)
{
	if (CharacterOwner && CharacterOwner->CanJump())
	{
		// Don't jump if we can't move up/down.
		if (!bConstrainToPlane || FMath::Abs(PlaneConstraintNormal.Z) != 1.f)
		{
			float velocityAngle = acos(FVector::DotProduct(Velocity.GetSafeNormal(), GravityDirection)) - (M_PI / 2);
			FVector upVelocity = Velocity * sin(velocityAngle);
			if (upVelocity.Size() < JumpZVelocity)
			{
				Velocity = (Velocity * cos(velocityAngle)) + (upVelocity.GetSafeNormal() * JumpZVelocity);
			}
			//Velocity.Z = FMath::Max(Velocity.Z, JumpZVelocity);
			SetMovementMode(MOVE_Falling);
			return true;
		}
	}

	return false;
}