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
	vector <shared_ptr<Vehicle>> vehicles; // vehicles at the station
	vector <shared_ptr<Train>> trains; // trains ready to leave...
	//vector<string> stations;

public:
	Station(string name, vector <shared_ptr<Vehicle>> vehicles): name(name), vehicles(vehicles){}
	~Station() {}

	
	void addVehicle(shared_ptr<Vehicle> vehicle) { vehicles.push_back(vehicle); }
	//shared_ptr<Vehicle> findVehicle(shared_ptr<Vehicle> vehicle); 
	//bool removeVehicle(shared_ptr<Vehicle> vehicle); 
	int getId() { return id; }
	string getName() { return name; }
	void display(){}

};

#endif
