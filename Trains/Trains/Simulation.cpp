/*
File: Simulation.cpp
Purpose: Implementation of class Simulation
Author: Örjan Sterner
Modified by: Eva Frisell <evmo1600>
Date: 2018-06-11
Version: 1.1
*/
#include "Simulation.h"
#include "Event.h"
#include <algorithm>
// Execute events until event queue is empty
void Simulation::run()
{
	while (!eventQueue.empty()) {
		Event * nextEvent = eventQueue.top();
		eventQueue.pop();
		currentTime = nextEvent->getTime();
		nextEvent->processEvent();
		delete nextEvent;
	}
}

void Simulation::scheduleEvent(Event * newEvent) {
	eventQueue.push(newEvent);
}
