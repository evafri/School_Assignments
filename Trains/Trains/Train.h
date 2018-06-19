/*
File: Train.h
Purpose: Holds information about the actual train, a combination of vehicles
Author: Eva Frisell <evmo1600>
Date: 2018-06-11
Version: 1.1
*/

#ifndef TRAIN_H
#define TRAIN_H

#include <iostream>
#include "Vehicle.h"
#include "Station.h"
#include <memory>
#include <vector>

using namespace std;

class Train {

private:
	int id;
	vector <shared_ptr<Vehicle>> vehicles;  
	vector <string> vehicleTypes;  
	string depStation;
	string arrStation;
	int depTime;
	int arrTime;
	string schedArrTime;
	string schedDepTime;
	double maxSpeed;
	bool isLate;

public:
	Train(int id, vector<string>vehicleTypes, string depStation, string arrStation, string schedDepTime, string schedArrTime, double maxSpeed ) : id(id), vehicleTypes(vehicleTypes),
	depStation(depStation), arrStation(arrStation), schedDepTime(schedDepTime), schedArrTime(schedArrTime), maxSpeed(maxSpeed){}
	~Train(){}

	//bool addVehicles(); 
	//bool unloadVehicles(); 

	string getSchedDepTime() { return schedDepTime; }
	string getSchedArrTime() { return schedArrTime; }
	int getDepTime() { return depTime; }
	int getId() { return id; }
	int getArrTime() { return arrTime; }
	string getDepStation() { return depStation; }
	string getArrStation() { return arrStation; }
	bool getLate() { return isLate; }
	// set late
	// set time
	// states?
};
#endif