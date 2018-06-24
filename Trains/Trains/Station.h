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
	vector <shared_ptr<Vehicle>> vehicles; // vehicles at the station
//	vector <shared_ptr<Train>> trains; // trains ready to leave... needded?

public:
	Station(string name, vector <shared_ptr<Vehicle>> vehicles): name(name), vehicles(vehicles){}
	~Station() {}

	void addVehicleToStation(shared_ptr<Vehicle> vehicle); // lägga till vehicles till stationen
	bool findVehicle(shared_ptr<Vehicle> &vehicle, string type); // söka efter ett vehicle 
	
	bool removeVehicleAtStation(shared_ptr<Vehicle> vehicle); // ta bort ett vehicle från poolvektorn som lagts till
	int getId() { return id; }
	string getName() { return name; }
	string getType() { return type; }
	void print();
};

#endif
