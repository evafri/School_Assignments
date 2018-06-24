/*
File: OpenFreightCar.h
Purpose: Class that holds information about the cars that carry goods on the railway
Author: Eva Frisell <evmo1600>
Date: 2018-05-14
Version: 1.1
*/

#include "FreightCars.h"
#include <iostream>

using namespace std;

class OpenFreightCar : public FreightCars {
private:
	int loadingCapacity = 0;
	int loadingSurface = 0;

public:
	OpenFreightCar(int id, int loadCapacity, int loadSurface):FreightCars(id, "OpenFreightCar"),loadingCapacity(loadingCapacity),
		loadingSurface(loadingSurface){}
	~OpenFreightCar(){}
	virtual void print(ostream &os = cout) {
		Vehicle::print(os);
		os << "LoadingCapacity: " << loadingCapacity << endl;
		os << "LoadingSurface: " << loadingSurface << endl;
	}
};
