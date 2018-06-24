/*
File: Simulation.cpp
Purpose: Implementation of class Simulation
Author: Örjan Sterner
Modified by: Eva Frisell <evmo1600>
Date: 2018-06-11
Version: 1.1
*/

#include <fstream>
#include "Simulation.h"
#include "Event.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>
#include "Constants.h"

using namespace std;

// Execute events until event queue is empty
void Simulation::run(int startTime, int endTime, int interval, int simulationMode)
{
	bool keepOn = true;
	int currentMinute = startTime;
	while (keepOn) {
		keepOn = currentMinute < endTime;

		if (currentMinute % interval == 0 && simulationMode != 2) {
			if (simulationMode == 1) {
				system("pause");
			}
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
			string logEntry = currentHhFormat + to_string(currentHH) + ":" + currentMmFormat + to_string(currentMM) + "\n";
			logToFile(logEntry);
			cout << currentHhFormat << currentHH << ":" << currentMmFormat << currentMM << endl;
		}
		shared_ptr<Event> nextEvent = eventQueue.top();
		currentTime = nextEvent->getTime(); // Do we have any events to run at this moment?
		if (currentTime == currentMinute) {
			if (simulationMode == 2) {
				system("pause");
			}
			while (!eventQueue.empty()) {
				shared_ptr<Event> nextEvent = eventQueue.top();
				int currentEventTime = nextEvent->getTime(); // Is it time to handle event?
				if (currentEventTime == currentMinute) {
					eventQueue.pop();
					nextEvent->processEvent(keepOn);
				}
				else {
					break;
				}
			}
			if (!keepOn) { // we need to empty the queue and let every train which is running to arrive at their destination..
				while (!eventQueue.empty()) {
					shared_ptr<Event> nextEvent = eventQueue.top();
					eventQueue.pop();
					currentTime = nextEvent->getTime();
					nextEvent->processEvent(keepOn);
				}
			}
		}
		currentMinute++;
	}
}

void Simulation::scheduleEvent(shared_ptr<Event> newEvent) {
	eventQueue.emplace(newEvent);
}

void Simulation::logToFile(string logEntry)
{
	ofstream logFile("Trainsim.log", ios_base::out | ios_base::app);
	logFile << logEntry;
	logFile.close();
}