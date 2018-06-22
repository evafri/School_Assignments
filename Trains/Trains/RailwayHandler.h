/*
File: RailwayHandler.h
Purpose: Handles the railway and communicates with the other classes. RailwayHandler reads in the files needed for the simulation and
starts off the events.
Author: Eva Frisell <evmo1600>
Date: 2018-06-11
Version: 1.1
*/

#include <iostream>
#include "Station.h"
#include "Train.h"
#include "PassengerCar.h"
#include "SleepingCar.h"
#include "ClosedFreightCar.h"
#include "OpenFreightCar.h"
#include "ElectricalLocomotive.h"
#include "DieselLocomotive.h"
#include "StationDistance.h"
#include "Simulation.h"

using namespace std;

class RailwayHandler {

private:
	vector <shared_ptr<Vehicle>> vehicles;  
	vector<shared_ptr<Station>> stations;
	vector <shared_ptr<Train>> trains; 
	vector <shared_ptr<StationDistance>> stationDistance;
	Simulation *sim;

	shared_ptr<Vehicle> vehiclePointer;
	shared_ptr<Station> stationPointer;
	shared_ptr<Train> trainPointer;

public:
	RailwayHandler(Simulation *sim) : sim(sim){}
	~RailwayHandler() {}
	bool fileHandler(string stationfile, string trainfile, string trainmapfile);
	bool readStationsFromFile(string filename);
	bool readTrainsFromFile(string filename);
	bool readTrainMapFromFile(string filename);

	// funktion som startar upp event mm samt anropar add remove find i station/train
	// söker efter ett tåg id i trains skickar med, ska bygga ex 1

	void startEvents();
	bool build(int trainId);
	bool assembled(int trainId);
	bool isRunning(int trainId);
	bool arrived(int trainId);
	bool end(int trainId);

	void logToFile();
};
