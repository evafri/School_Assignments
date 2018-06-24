/*
File: Carriage.h
Purpose: Holds information about all the different carriages of the railway
Author: Eva Frisell <evmo1600>
Date: 2018-05-14
Version: 1.1
*/

#ifndef CARRIAGE_H
#define CARRIAGE_H

#include "Vehicle.h"
#include <iostream>

using namespace std;

class Carriage : public Vehicle {

public:
	Carriage(int id, string type) :Vehicle(id, type) {}
	~Carriage() {}
	virtual void print(ostream &os = cout) {}
};
#endif