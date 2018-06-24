/*
File: Main.cpp
Purpose: This is where the program starts. Main holds a menu where an user can make different choices regarding the simulation.
Author: Eva Frisell <evmo1600>
Date: 2018-05-14
Version: 1.1
*/

#include <iostream>
#include <fstream>
#include <string>
#include "Station.h"
#include "Simulation.h"
#include "RailwayHandler.h"
#include "memstat.hpp"

using namespace std;

int main() {

	Simulation *sim = new Simulation();
	RailwayHandler *railwayHandler = new RailwayHandler(sim);
	railwayHandler->fileHandler("TrainStations.txt", "Trains.txt", "TrainMap.txt");

	int startTime = 0;
	int endTime = 0;



	//int simTime = 0;
	//while (simTime < SIM_TIME) { // Load events into queue between 00:00 and 23:59		
	//	

	//	if (simTime >= SIM_TIME) { // Schedule the close down
	//		//theSim->scheduleEvent(new ClosingEvent(theSim, theBar, SIM_TIME))//;
	//	}
	//	else { // Schedule a new arrival
	//		//gör nåt här
	//	}	
	//	simTime++;
	//}

	//railwayHandler->startEvents();
	//sim->run();

	char choice;
	bool keepOn = true;
	bool queueHasEvents = true;
	railwayHandler->startEvents();
	

	do
	{
		cout << endl << " ***** MENU *****" << endl;
		cout << " 1. Change starttime and stoptime" << endl;
		cout << " 2. Change time interval" << endl;
		cout << " 3. Use time interval or let the simulation run" << endl;
		cout << " 4. Print timetable" << endl;
		cout << " 5. Print train" << endl;
		cout << " 6. Print station" << endl;
		cout << " 7. Run simulation" << endl;
		cout << " 8. Quit" << endl << endl;

		cout << "Please enter your choice: ";
		cin >> choice;

		switch (choice)
		{
		case '1':
		{
			//startTime = 0;
			//endTime = SIM_TIME;
			int newStartTime = 0;
			int newEndTime;
			cout << "Enter start time:" << endl;
			cin >> newStartTime;
			cout << "Enter stop time:" << endl;
			cin >> newEndTime;
			sim->run(newStartTime, newEndTime, TIME_INTERVAL_DEFAULT);
			break;
		}
		case '2':
		{
			int newTimeInterval;
			cout << "Enter new Time interval: " << endl;
			cin >> newTimeInterval;
			sim->run(startTime, endTime, newTimeInterval);
			break;
		}
		case '3':
		{ 
			if (queueHasEvents == true) {
				//run events löpa till nästa event?
				keepOn = false;
			}
			else {
				cout << "Run simulation by " << TIME_INTERVAL << " minutes" << endl;
				sim->run(startTime, endTime, TIME_INTERVAL);
			}
			// run events or use interval skicka upp 10 min

			break;
		}
		case '4':
		{
			break;
		}
		case '5':
		{
			int trainId;
			cout << "Enter Train id" << endl;
			cin >> trainId;
			railwayHandler->printTrain(trainId);
			break;
		}
		case '6':
		{
			string name;
			cout << "Enter Station name" << endl;
			cin >> name;
			railwayHandler->printStation(name);
			break;
		}
		case '7':
		{
			sim->run(startTime, endTime, TIME_INTERVAL_DEFAULT);
			break;
		}
		default: keepOn = false;
			break;
		}
	} while (keepOn);

	delete sim;
	delete railwayHandler;

	return 0;
}