// Fill out your copyright notice in the Description page of Project Settings.


#include "SGameMode.h"
#include "SGamePlayerState.h"
#include "SInteractActor_CheckPoint.h"

int ASInteractActor_CheckPoint::CPNumber = 0;
ASInteractActor_CheckPoint* ASInteractActor_CheckPoint::LastCheckPoint = nullptr;

ASGameMode::ASGameMode()
{
	PlayerStateClass = ASGamePlayerState::StaticClass();
}
