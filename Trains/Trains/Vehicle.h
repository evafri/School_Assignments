/*
File: Vehicle.h
Purpose: Vehicle is a baseclass that holds information about the vehicles of the railway.
Author: Eva Frisell <evmo1600>
Date: 2018-05-14
Version: 1.1
*/

#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <string>

using namespace std;

class Vehicle {
protected:
	int id;
	string type;

public:
	Vehicle(int id, string type):id(id),type(type){}
	~Vehicle(){}
	int getId() { return id; }
	string getType() { return type; }
	virtual void print(ostream &os = cout) {
		os << "Vehicle id: " << id << endl;
		os	<< "Vehicle type: " << type << endl;
	}
};

#endif
