// Fill out your copyright notice in the Description page of Project Settings.


#include "Laser/SLaserSensor.h"
#include "Laser/SLaserInterface.h"


void ASLaserSensor::SetState_Implementation(AActor* InstigatorActor, bool NewState)
{
	ISLaserSensorInterface::SetState_Implementation(InstigatorActor, NewState);

	for(AActor* Actor : InteractActors)
	{
		if(Actor->Implements<USLaserInterface>())
		{
			ISLaserInterface::Execute_LaserInteract(Actor,this,NewState);
		}
	}
}



