/*
File: DieselLocomotive.h
Purpose: Holds information about the diesel locomotives on the railway
Author: Eva Frisell <evmo1600>
Date: 2018-05-14
Version: 1.1
*/

#pragma once
#include "Locomotive.h"
#include <iostream>

using namespace std;

class DieselLocomotive : public Locomotive {
private:
	int maxSpeedInKm;
	double fuelConsumption;

public:
	DieselLocomotive(int id, int maxSpeedInKm, double fuelConsumption):Locomotive(id, "dieselLocomotive"),
		maxSpeedInKm(maxSpeedInKm), fuelConsumption(fuelConsumption) {}
	~DieselLocomotive(){}
	void print(ostream &os) {
		os << "Max speed (km): " << maxSpeedInKm << endl;
		os << "Fuel consumption: " << fuelConsumption << endl;
	}
};
