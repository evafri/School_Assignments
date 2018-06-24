/*
File: Event.cpp
Purpose: Implementation of derived Event classes. A train travels through the different events.
Author: Örjan Sterner
Modified by: Eva Frisell <evmo1600>
Date: 2018-06-11
Version: 1.1
*/

#include "Event.h"
#include "Simulation.h"
#include "RailwayHandler.h"
#include <memory>

// Event function that handles the beginning of a trains journey. If a train is assembled it travels into the ready event
void BuildEvent::processEvent()
{
	shared_ptr<Event> e;

	if (railwayHandler->build(trainId)) // checks if it is possible to build a train. If train is assembled a new readyevent starts
	{
		time += TIME_READY;					// Train is ready to depart
		e = shared_ptr<Event>(new ReadyEvent(sim, railwayHandler, time, trainId));
		sim->scheduleEvent(e);
	}
	// If a train is delayed...TODO implement functions that handles delay.
	else {
		time += TIME_DELAY;					// Train is delayed
		e = shared_ptr<Event>(new BuildEvent(sim, railwayHandler, time, trainId));
		sim->scheduleEvent(e);
	}
	
}

// Function that creates a leave event
void ReadyEvent::processEvent()
{
	shared_ptr<Event> e;
	int depTime;						// variable used for saving a trains schedule depature time
	depTime = railwayHandler->assembled(trainId);
	time = depTime;									// Set time to trains departure time
	e = shared_ptr<Event>(new LeaveEvent(sim, railwayHandler, time, trainId));
	sim->scheduleEvent(e);

}

// Fuction that creates an arrive event
void LeaveEvent::processEvent()
{
	shared_ptr<Event> e;
	int arrivalTime;						// variable used for saving a trains schedule arrival time
	arrivalTime	= railwayHandler->isRunning(trainId);
	time = arrivalTime;						// set time to trains arrival time
	e = shared_ptr<Event>(new ArriveEvent(sim, railwayHandler, time, trainId));
	sim->scheduleEvent(e);
}

// Function that creates a finish event
void ArriveEvent::processEvent()
{
	shared_ptr<Event> e;
	railwayHandler->arrived(trainId);
	time += TIME_FINISHED;						// Set time to finished
	e = shared_ptr<Event>(new FinishEvent(sim, railwayHandler, time, trainId));
	sim->scheduleEvent(e);
}

// Function that calls end function for train in railwayhandler class, and a trains journey ends.
void FinishEvent::processEvent()
{
	railwayHandler->end(trainId);
}

