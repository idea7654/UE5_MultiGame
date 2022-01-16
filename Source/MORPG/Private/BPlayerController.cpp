// Fill out your copyright notice in the Description page of Project Settings.


#include "BPlayerController.h"
#include "..\Public\BPlayerController.h"
#include "ClientSocket.h"

ABPlayerController::ABPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

ABPlayerController::~ABPlayerController()
{
	delete Socket;
}

void ABPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Hello World"));
	Socket = new ClientSocket("ClientSocket");
	if (Socket->Begin())
		Socket->Connect();
}

void ABPlayerController::EndOfPlay()
{
	
}

void ABPlayerController::Tick(float DeltaSeconds)
{

}
