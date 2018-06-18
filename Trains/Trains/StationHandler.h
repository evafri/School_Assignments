/*
File: StationHandler.h
Purpose: Handles the station
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

using namespace std;

class StationHandler {

private:
	vector <shared_ptr<Vehicle>> vehicles; // vector 
	vector<shared_ptr<Station>> stations;
	// Sim anknytning

public:
	StationHandler(){}
	~StationHandler() {}
	bool readFromFileHandler(string stationfile);
	bool readStationsFromFile(string filename);
	void readTrainsFromFile(string filename);
	void readTrainMapFromFile(string filename);

};
