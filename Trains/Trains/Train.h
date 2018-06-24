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
#include "StationDistance.h"
#include "Constants.h"
#include <memory>
#include <vector>

using namespace std;

class Train {

private:
	int id;
	vector <shared_ptr<Vehicle>> vehicles;  
	vector <shared_ptr<Vehicle>> train;
	vector <string> vehicleTypes;  
	
	vector <shared_ptr<StationDistance>> stationDistance;
	string depStation;
	string arrStation;
	int depTime;
	int arrTime;
	string schedArrTime;
	string schedDepTime;
	double maxSpeed;
	bool isLate;
	State state; 

public:
	Train(int id, vector<string>vehicleTypes, string depStation, string arrStation, string schedDepTime, string schedArrTime, double maxSpeed ) : id(id), vehicleTypes(vehicleTypes),
	depStation(depStation), arrStation(arrStation), schedDepTime(schedDepTime), schedArrTime(schedArrTime), maxSpeed(maxSpeed){
		isLate = false;			// default value
		state = NOT_ASSEMBLED; // default value
	}
	~Train(){}

	void addVehiclesToTrain(shared_ptr<Vehicle> vehicle);
	bool unloadVehiclesFromTrain(shared_ptr<Vehicle> vehicle);

	string getSchedDepTime() { return schedDepTime; }
	string getSchedArrTime() { return schedArrTime; }
	int getDepTime() { return depTime; }
	void setDepTime(int time) { depTime = time; }
	int getId() { return id; }
	int getArrTime() { return arrTime; }
	string getDepStation() { return depStation; }
	string getArrStation() { return arrStation; }
	bool getIsLate() { return isLate; }
	State getState() { return state; }
	void setState(State iState) { state = iState; }
	void setIslate(bool late) { isLate = late; }
	void setDelay(int time);
	
	vector<string> getType() { return vehicleTypes; }
	double getMaxSpeed() { return maxSpeed; }
	double calculateAverageSpeed(int distance);
	void print(double sum);
};
#endif