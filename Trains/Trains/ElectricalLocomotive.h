/*
File: ElectricalLocomotive.h
Purpose: Holds information about the electrical locomotives on the railway
Author: Eva Frisell <evmo1600>
Date: 2018-05-14
Version: 1.1
*/

#include "Locomotive.h"
#include <iostream>

using namespace std;

class ElectricalLocomotive : public Locomotive {
private:
	int maxSpeedInKm;
	int powerInKw;
public:
	ElectricalLocomotive(int id, int maxSpeedInKm, int powerInKw):Locomotive(id, "electricalLocomotive"),
		maxSpeedInKm(maxSpeedInKm),powerInKw(powerInKw){}
	~ElectricalLocomotive(){}
	void print(ostream &os = cout) {
		Vehicle::print(os);
		os << "Max speed (km): " << maxSpeedInKm << endl;
		os << "Power (kW): " << powerInKw << endl;
	}
};
