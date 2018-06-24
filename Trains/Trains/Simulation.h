/*
File: Simulation.h
Purpose: Definition of class Simulation, a framework for discrete event-driven simulation
Author: Örjan Sterner
Modified by: Eva Frisell <evmo1600>
Date: 2018-06-11
Version: 1.1
*/

#ifndef SIMULATION_H
#define SIMULATION_H

#include <queue>
#include <vector>
#include "Event.h"
#include <memory>

using namespace std;
using std::priority_queue;
using std::vector;

class Simulation {
public:
	Simulation() : currentTime(0), eventQueue() { }

	~Simulation() {}
	// Add a new event to event queue.
	//void scheduleEvent(Event * newEvent);
	void scheduleEvent(shared_ptr<Event> newEvent);
	int getTime() const { return currentTime; }

	void run(int startTime, int endTime, int interval, int simulationMode);
	void logToFile(string logEntry);

private:
	int currentTime; // Time for last processed event

					 /* The event queue. Always sorted with respect to the times
					 for the events. The event with the 'smallest' time is always
					 placed first in queue and will be processed next. */

					 //priority_queue<Event*, vector<Event*>, EventComparison> eventQueue;
	priority_queue<shared_ptr<Event>, vector<shared_ptr<Event>>, EventComparison> eventQueue;
};

#endif

