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

using namespace std;

// Execute events until event queue is empty
void Simulation::run(int startTime, int endTime, int timestamp)
{
	int currentMinute = startTime;

	while (currentMinute <= endTime) {
		cout << "CurrentMinute: " << currentMinute << endl;

		shared_ptr<Event> nextEvent = eventQueue.top();
		currentTime = nextEvent->getTime(); // do we have any eventsto run at this moment?

		if (currentTime == currentMinute) {

			cout << "run one or more events now" << endl;


			while (!eventQueue.empty()) {
				
				shared_ptr<Event> nextEvent = eventQueue.top();
				int currentEventTime = nextEvent->getTime(); // is it time to handle event?
				
				if (currentEventTime == currentMinute) {
					eventQueue.pop();
					nextEvent->processEvent();
					//delete nextEvent;
				}
				else {
					break;
				}
			}

		}

		//while (!eventQueue.empty()) {
		//	Event * nextEvent = eventQueue.top();
		//	currentTime = nextEvent->getTime(); // is it time to handle event?
		//	if (currentTime == currentMinute) {
		//		eventQueue.pop();
		//		//currentTime = nextEvent->getTime();
		//		nextEvent->processEvent();
		//		delete nextEvent;
		//	}
		//}
		currentMinute++;
	}


	/*
	while (!eventQueue.empty()) {
		
		
		Event * nextEvent = eventQueue.top();
		
		currentTime = nextEvent->getTime();
		if (currentTime == currentMinute) {

		}
		/*
		eventQueue.pop();
		currentTime = nextEvent->getTime();
		nextEvent->processEvent();
		delete nextEvent;
		/
		

	}*/
}

void Simulation::scheduleEvent(shared_ptr<Event> newEvent) {
	eventQueue.emplace(newEvent);
}
