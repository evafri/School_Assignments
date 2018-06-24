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
	vector <shared_ptr<Train>> assembledTrains;
	vector <shared_ptr<Train>> incompleteTrains;
	shared_ptr<Vehicle> vehiclePointer = nullptr;
	vector<string>vehicleTypes;
	bool runWithDefaultInterval;

public:
	RailwayHandler(Simulation *sim) : sim(sim){ }
	~RailwayHandler() {}
	bool fileHandler(string stationfile, string trainfile, string trainmapfile);
	bool readStationsFromFile(string filename);
	bool readTrainsFromFile(string filename);
	bool readTrainMapFromFile(string filename);
	void startEvents();
	bool build(int trainId);
	void assembled(int trainId);
	int isRunning(int trainId);
	void arrived(int trainId);
	void end(int trainId);
	double calculateAverageSpeed(int trainId);
	void logToFile();
	void printTrain(int trainId);
	void printStation(string name);
	void setRunWithDefaultInterval(bool value);
};
