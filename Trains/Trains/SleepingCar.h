/*
File: SleepingCar.h
Purpose: Class that holds information about the sleeping cars on the railway
Author: Eva Frisell <evmo1600>
Date: 2018-05-14
Version: 1.1
*/

#include "Cars.h"
#include <iostream>

using namespace std;

class SleepingCar : public Cars {
private:
	int beds;

public:
	SleepingCar(int id, int beds) :Cars(id, "SleepingCar"),beds(beds) {}
	~SleepingCar(){}
	void print(ostream &os = cout) {
		Vehicle::print(os);
		os << "beds: " << beds << endl;
	}
};
