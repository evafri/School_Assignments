/*
File: Cars.h
Purpose: Abstract class for the two different types of cars that transport people on the railway
Author: Eva Frisell <evmo1600>
Date: 2018-05-14
Version: 1.1
*/

#include "Carriage.h"
#include <iostream>

using namespace std;

class Cars : public Carriage {
public:
	Cars(int id, string type) :Carriage(id, type) {}
	~Cars() {}
	void print(ostream &os) = 0;
};

