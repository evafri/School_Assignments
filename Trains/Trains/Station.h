/*
File: Station.h
Purpose: Holds information about the stations on the railway
Author: Eva Frisell <evmo1600>
Date: 2018-06-11
Version: 1.1
*/

#ifndef STATION_H
#define STATION_H

#include <iostream>
#include <vector>
#include <memory>
#include "Vehicle.h"
#include "Train.h"

class Station {

private:
	int id;
	string name;
	string type;
	vector <shared_ptr<Vehicle>> vehicles; // vehicles at the station that holds all the different vehicles
//	vector <shared_ptr<Train>> trains; // trains ready to leave... needed?

public:
	Station(string name, vector <shared_ptr<Vehicle>> vehicles): name(name), vehicles(vehicles){}
	~Station() {}

	void addVehicleToStation(shared_ptr<Vehicle> vehicle); 
	bool findVehicle(shared_ptr<Vehicle> &vehicle, string type); 
	
	bool removeVehicleAtStation(shared_ptr<Vehicle> vehicle); 
	int getId() { return id; }
	string getName() { return name; }
	string getType() { return type; }
	void print();
};

#endif
