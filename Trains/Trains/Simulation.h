/*
File: Simulation.h
Purpose: Definition of class Simulation, a framework for discrete event-driven simulation
Author: �rjan Sterner
Modified by: Eva Frisell <evmo1600>
Date: 2018-06-11
Version: 1.1
*/

#ifndef SIMULATION_H
#define SIMULATION_H

#include <queue>
#include <vector>
#include "Event.h"

using std::priority_queue;
using std::vector;

class Simulation {
public:
	Simulation() : currentTime(0), eventQueue() { }

	// Add a new event to event queue.
	void scheduleEvent(Event * newEvent);

	int getTime() const { return currentTime; }

	void run();

private:
	int currentTime; // Time for last processed event

					 /* The event queue. Always sorted with respect to the times
					 for the events. The event with the 'smallest' time is always
					 placed first in queue and will be processed next. */

	priority_queue<Event*, vector<Event*>, EventComparison> eventQueue;
};

#endif
