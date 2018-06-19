/*
File: Locomotive.h
Purpose: Holds information about all the different locomotives on the railway
Author: Eva Frisell <evmo1600>
Date: 2018-05-14
Version: 1.1
*/

#pragma once
#include "Vehicle.h"
#include <iostream>

using namespace std;

class Locomotive : public Vehicle {
public:
	Locomotive(int id, string type): Vehicle(id, type){}
	~Locomotive(){}
	virtual void print(ostream &os) = 0;
};