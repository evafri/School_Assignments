/*
File: Main.cpp
Purpose: This is where the program starts. Main holds a menu where an user can make different choices regarding the simulation.
Author: Eva Frisell <evmo1600>
Date: 2018-05-14
Version: 1.1
*/

#include <iostream>
#include <string>
#include "Station.h"
#include "Simulation.h"
#include "RailwayHandler.h"
#include "memstat.hpp"
#include <fstream>
#include <sstream>

using namespace std;

int main() {

	Simulation *sim = new Simulation();
	RailwayHandler *railwayHandler = new RailwayHandler(sim);
	railwayHandler->fileHandler("TrainStations.txt", "Trains.txt", "TrainMap.txt");

	int startTime = 0;
	int endTime = 0;

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
			int newStartTime = 0;
			int newEndTime = 0;
			string startTime;
			string endTime;
			char delim;
			int startTimeHh = 0;
			int startTimeMm = 0;
			int endTimeHh = 0;
			int endTimeMm = 0;

			cout << "Enter start time [hh:mm]:" << endl;
			cin >> startTime;
			cout << "Enter stop time [hh:mm]:" << endl;
			cin >> endTime;

			istringstream iss;
			iss.str(startTime);
			iss >> startTimeHh >> delim >> startTimeMm;
			if (startTimeHh < 0 || startTimeHh > 23 || startTimeMm < 0 || startTimeMm > 59) {
				startTimeHh = 0;
				startTimeMm = 0;
				cout << "Invalid starttime, setting default starttime." << endl;
			}

			istringstream iss2;
			iss2.str(endTime);
			iss2 >> endTimeHh >> delim >> endTimeMm;
			if (endTimeHh < 0 || endTimeHh > 23 || endTimeMm < 0 || endTimeMm > 59) {
				endTimeHh = 23;
				endTimeMm = 59;
				cout << "Invalid endtime, setting default starttime." << endl;
			}

			newStartTime = startTimeHh * 60 + startTimeMm;
			newEndTime = endTimeHh * 60 + endTimeMm;

			if (newStartTime >= newEndTime) {
				newStartTime = 0;
				endTimeHh = 23;
				endTimeMm = 59;
				newEndTime = endTimeHh * 60 + endTimeMm;
				cout << "Error: Starttime can be after endtime, setting default values." << endl;
			}
			railwayHandler->setRunWithDefaultInterval(true);
			cin.get();
			railwayHandler->pressToContinue();
			sim->run(newStartTime, newEndTime, TIME_INTERVAL_DEFAULT, -1);
			break;
		}
		case '2':
		{
			int newTimeInterval;
			cout << "Enter new Time interval: " << endl;
			cin >> newTimeInterval;
			if (newTimeInterval < 1 || newTimeInterval >= SIM_TIME) {
				cout << "Invalid time interval, setting default value(1): " << endl;
				newTimeInterval = TIME_INTERVAL_DEFAULT;
			}
			railwayHandler->setRunWithDefaultInterval(newTimeInterval == TIME_INTERVAL_DEFAULT);
			cin.get();
			railwayHandler->pressToContinue();
			sim->run(0, SIM_TIME, newTimeInterval, -1);
			break;
		}
		case '3':
		{
			cin.get();
			int choice;
			cout << "Press 0 to step through simulation using 10 minutes interval" << endl;
			cout << "Press 1 to move simulation to next event" << endl;
			cin >> choice;
			cin.get();
			if (choice < 0 || choice > 1) {
				cout << "Invalid input" << endl;
				cout << "Stepping through simulation" << endl;
			}
			if (choice == 0) {
				sim->run(0, SIM_TIME, TIME_INTERVAL, 1);
			}
			if (choice == 1) {
				sim->run(0, SIM_TIME, TIME_INTERVAL, 2);
			}
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
			railwayHandler->setRunWithDefaultInterval(true);
			sim->run(0, SIM_TIME, TIME_INTERVAL_DEFAULT, -1);
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