// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DirectionalGravityComponent.generated.h"


class AGAME259_A_URECharacter;
class UCharacterMovementComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GAME259_A_URE_API UDirectionalGravityComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDirectionalGravityComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector Direction = FVector(0.0f, 0.0f, -1.0f);

	FRotator TargetRotation;
	//FRotator ControllerRotation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float RotationShiftSpeed = 1.0;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Strength = 980.0f;

	AGAME259_A_URECharacter* Character;
	UCharacterMovementComponent* Movement;

	UFUNCTION(Blueprintcallable)
	void SetGravity(const FVector& newDirection, float newStrength, FRotator newRotation);

	virtual bool DoJump(bool bReplayingMoves);
};
