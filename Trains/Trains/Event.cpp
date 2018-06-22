/*
File: Event.cpp
Purpose: Implementation of Event
Author: Örjan Sterner
Modified by: Eva Frisell <evmo1600>
Date: 2018-06-11
Version: 1.1
*/

#include "Event.h"
#include "Simulation.h"
#include "RailwayHandler.h"

void BuildEvent::processEvent()
{
	if (railwayHandler->build(trainId)) // kolla om det går att bygga med find add mm försenat incomplete
	{
		time += TIME_READY;
		Event *e = new readyEvent(sim, railwayHandler, time, trainId);
		sim->scheduleEvent(e);
	}
	else {
		time += TIME_DELAY;
		Event *e = new BuildEvent(sim, railwayHandler, time, trainId);
		sim->scheduleEvent(e);
	}

}

void readyEvent::processEvent()
{
	railwayHandler->assembled(trainId);
	time += TIME_DEPARTURE;
	Event *e = new LeaveEvent(sim, railwayHandler, time, trainId);
	sim->scheduleEvent(e);

}

void LeaveEvent::processEvent()
{
	int arrivalTime;
	arrivalTime	= railwayHandler->isRunning(trainId);
	time = arrivalTime;
	Event *e = new ArriveEvent(sim, railwayHandler, time, trainId);
	sim->scheduleEvent(e);
}

void ArriveEvent::processEvent()
{
	railwayHandler->arrived(trainId);
	time += TIME_FINISHED;
	Event *e = new FinishEvent(sim, railwayHandler, time, trainId);
	sim->scheduleEvent(e);

}

void FinishEvent::processEvent()
{
	railwayHandler->end(trainId);

}

