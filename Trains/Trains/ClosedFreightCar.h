/*
File: ClosedFreightCar.h
Purpose: Class that holds information about the cars that carry goods on the railway
Author: Eva Frisell <evmo1600>
Date: 2018-05-14
Version: 1.1
*/

#include "FreightCars.h"
#include <iostream>

using namespace std;

class ClosedFreightCar : public FreightCars {
private:
	int loadingVolume;

public:
	ClosedFreightCar(int id, int loadingVolume) :FreightCars(id, "ClosedFreightCar"),loadingVolume(loadingVolume){}
	~ClosedFreightCar(){}
	virtual void print(ostream &os) {
		os << "Loading Volume: " << loadingVolume << endl;
	}
};
