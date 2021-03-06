// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BCharacter.generated.h"

UCLASS()
class MORPG_API ABCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FVector MoveDirection;

	void MoveForward(float Value);
	void MoveRight(float Value);
	void Move(float Value);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
