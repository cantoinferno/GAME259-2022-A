// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GravityMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class GAME259_A_URE_API UGravityMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	virtual bool DoJump(bool bReplayingMoves) override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector GravityDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FRotator Orientation;
};
