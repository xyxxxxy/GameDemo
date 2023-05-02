// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/Engine.h"

#define DISPLAY_SCREEN(Text) GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Red,FString::Printf(TEXT("Screen : %s"),*(FString(Text))))
#define DISPLAY_LOG(Text) UE_LOG(LogTemp,Warning,TEXT("Log : %s"),*FString(Text))
