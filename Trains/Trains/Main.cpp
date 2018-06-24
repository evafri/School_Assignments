/*
File: Main.cpp
Purpose: This is where the program starts
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

using namespace std;

int main() {

	Simulation *sim = new Simulation();
	RailwayHandler *railwayHandler = new RailwayHandler(sim);
	railwayHandler->fileHandler("TrainStations.txt", "Trains.txt", "TrainMap.txt");

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



	railwayHandler->startEvents();
	sim->run();
		

	// starta event
	// starta sim run()

	// menyer mm

	char choice; 
	bool keepOn = true;

	do
	{
		cout << endl << " ***** MENU *****" << endl;
		cout << " 1. Change starttime and stoptime" << endl;
		cout << " 2. Use time interval" << endl;
		cout << " 3. Change time interval" << endl; // eller låta simuleringen löpa vidare
		cout << " 4. Print timetable" << endl;
		cout << " 5. Print train" << endl; 
		cout << " 6. Print station" << endl; 
		cout << " 7. Quit" << endl << endl;

		cout << "Please enter your choice: ";
		cin >> choice;

		switch (choice)
		{
		case '1':
		{
			// run()

			break;
		}
			case '2':
			{
				// set simhasevents false if events are stopped
				// run()
				break;
			}
			


		case '3':
		{
			// set simhasevents false if events are stopped
			// run()
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
		
		default: keepOn = false;
			break;
		}
	} while (keepOn);

	delete sim;
	delete railwayHandler;

	return 0;
}