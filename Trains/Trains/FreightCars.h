/*
File: FreightCars.h
Purpose: Abstract class for the two different types of cars that transport goods on the railway
Author: Eva Frisell <evmo1600>
Date: 2018-05-14
Version: 1.1
*/

#include "Carriage.h"
#include <iostream>

using namespace std;

class FreightCars : public Carriage {
public:
	FreightCars(int id, string type) :Carriage(id, type) {}
	~FreightCars() {}
	void print(ostream &os) = 0;
};
