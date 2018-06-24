/*
File: Train.cpp
Purpose: Implementation of Train
Author: Eva Frisell <evmo1600>
Date: 2018-06-11
Version: 1.1
*/

#include "Train.h"
#include <fstream>
#include <sstream>
#include <iostream>

void Train::addVehiclesToTrain(shared_ptr<Vehicle> vehicle)
{
	//add to train
	train.emplace_back(vehicle);
}

bool Train::unloadVehiclesFromTrain(shared_ptr<Vehicle> vehicle)
{
	shared_ptr<Station> sp;
	auto item = std::find(train.begin(), train.end(), vehicle);

	if (item == train.end()) {
		return false;
	}
	else {
		train.erase(item);
		sp->addVehicleToStation(vehicle);
		return true;
	}
	return false;
}

void Train::setDelay(int time)
{
	arrTime += time;
	depTime += time;
}

double Train::calculateAverageSpeed(int distance)
{
	istringstream iss;
	int hh, mm;
	char delim;
	int schedDepTimeConverted;
	int schedArrTimeConverted;

	iss.str(this->getSchedDepTime());
	iss >> hh >> delim >> mm;
	schedDepTimeConverted = (hh * 60 + mm);

	iss.str(this->getSchedArrTime());
	iss >> hh >> delim >> mm;
	schedArrTimeConverted = (hh * 60 + mm);

	// get distance ett tågs från station == från 
	double sum = 0;
	sum = distance / (schedArrTimeConverted - schedDepTimeConverted / 60);
	return sum;
}

void Train::print(double sum) {

	istringstream iss;
	int hh, mm;
	char delim;
	int schedDepTimeConverted;

	iss.str(this->getSchedDepTime());
	iss >> hh >> delim >> mm;
	schedDepTimeConverted = (hh * 60 + mm);

	cout << endl << "Train id: " << id << endl;
	cout << "State: " << state << endl;
	cout << "Departure: " << depTime << " from station " << depStation << endl;
	cout << "Arrival: " << arrTime << " at station " << arrStation << endl;
	cout << "Average speed: " << sum << endl;
	if (isLate) cout << "Running late by " << depTime - schedDepTimeConverted << " minutes" << endl;

	cout << "vehicles in train: " << endl << endl;

	//print all vehicles in train or vehicle or vehicletype?
	
	for (auto t : train) {

			t->print();
		
	}
}

