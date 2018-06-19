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
#include "StationDistance.h"

using namespace std;

class StationHandler {

private:
	vector <shared_ptr<Vehicle>> vehicles;  
	vector<shared_ptr<Station>> stations;
	vector <shared_ptr<Train>> trains; 
	vector <shared_ptr<StationDistance>> stationDistance;
	// Sim anknytning

public:
	StationHandler(){}
	~StationHandler() {}
	bool readFromFileHandler(string stationfile, string trainfile, string trainmapfile);
	bool readStationsFromFile(string filename);
	bool readTrainsFromFile(string filename);
	bool readTrainMapFromFile(string filename);

};
