// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameMode.h"
#include "SGamePlayerState.h"


ASGameMode::ASGameMode()
{
	PlayerStateClass = ASGamePlayerState::StaticClass();
}
