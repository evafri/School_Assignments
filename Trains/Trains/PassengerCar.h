/*
File: PassengerCar.h
Purpose: Class that holds information about the passenger cars on the railway
Author: Eva Frisell <evmo1600>
Date: 2018-05-14
Version: 1.1
*/

#include "Cars.h"
#include <iostream>

using namespace std;

class PassengerCar : public Cars {
private:
	int nrOfSeats;
	bool internet;

public:
	PassengerCar(int id, int nrOfSeats, bool internet) :Cars(id, "PassengerCar"),nrOfSeats(nrOfSeats), internet(internet){}
	~PassengerCar(){}
	virtual void print(ostream &os = cout) {
		Vehicle::print(os);
		os << "Number of seats: " << nrOfSeats << endl;
		os << "Internet: " << internet << endl;
	}
};
