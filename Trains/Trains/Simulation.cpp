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
#include <iostream>
#include <memory>
#include <string>
#include "Constants.h"

using namespace std;

// Execute events until event queue is empty
void Simulation::run(int startTime, int endTime, int interval)
{
	int currentMinute = startTime;
	while (currentMinute <= endTime) {
		if (currentMinute % interval == 0) {
			int currentHH = currentMinute / 60;
			int currentMM = currentMinute % 60;
			string currentHhFormat = "";
			string currentMmFormat = "";
			if (currentHH < 10) {
				currentHhFormat = "0";
			}
			if (currentMM < 10) {
				currentMmFormat = "0";
			}
			cout << currentHhFormat << currentHH << ":" << currentMmFormat << currentMM << endl;
		}
		shared_ptr<Event> nextEvent = eventQueue.top();
		currentTime = nextEvent->getTime(); // do we have any events to run at this moment?
		if (currentTime == currentMinute) {
			while (!eventQueue.empty()) {
				shared_ptr<Event> nextEvent = eventQueue.top();
				int currentEventTime = nextEvent->getTime(); // is it time to handle event?
				if (currentEventTime == currentMinute) {
					eventQueue.pop();
					nextEvent->processEvent();
				}
				else {
					break;
				}
			}
		}
		currentMinute++;
	}
}

void Simulation::scheduleEvent(shared_ptr<Event> newEvent) {
	eventQueue.emplace(newEvent);
}
