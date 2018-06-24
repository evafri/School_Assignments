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

// Function that adds a vehicle to the train
void Train::addVehiclesToTrain(shared_ptr<Vehicle> vehicle)
{
	//add to train
	train.emplace_back(vehicle);
}

// Function that removes a vehicle from the train
bool Train::unloadVehiclesFromTrain(shared_ptr<Vehicle> vehicle)
{
	auto item = std::find(train.begin(), train.end(), vehicle);

	if (item == train.end()) {
		return false;
	}
	else {
		train.erase(item);
		return true;
	}
	return false;
}

// Function that sets delay. TO DO implement delay functions.
void Train::setDelay(int time)
{
	arrTime += time;
	depTime += time;
}

// Function that calculates a trains average speed. TO DO handle delays.
double Train::calculateAverageSpeed(int distance)
{
	// Convert string into int for calculation
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

	double sum = 0;
	sum = distance / (schedArrTimeConverted - schedDepTimeConverted / 60);
	return sum;
}

// Function that prints 
void Train::print(double sum) {

	// convert string to int for calculation
	istringstream iss;
	int hh, mm;
	char delim;
	int schedDepTimeConverted;

	iss.str(this->getSchedDepTime());
	iss >> hh >> delim >> mm;
	schedDepTimeConverted = (hh * 60 + mm);

	int state = this->getState();
	string convertedState = "";

	if (state == 0) {
		convertedState = "NOT_ASSEMBLED";
	}
	else if (state == 1) {
		convertedState = "INCOMPLETE";
	}
	else if (state == 2) {
		convertedState = "ASSEMBLED";
	}
	else if (state == 3) {
		convertedState = "READY";
	}
	else if (state == 4) {
		convertedState = "RUNNING";
	}
	else if (state == 5) {
		convertedState = "ARRIVED";
	}
	else {
		convertedState = "FINISHED";
	}
	cout << endl << "Train id: " << id << endl;
	cout << "State: " << convertedState << endl;
	cout << "Departure: " << getSchedDepTime() << " from station " << depStation << endl;
	cout << "Arrival: " << getSchedArrTime() << " at station " << arrStation << endl;
	cout << "vehicles in train: " << vehicles.size() << endl << endl;
	for (auto vehicle : vehicles) {
		string typeName;
		if (vehicle.get()->getType() == "0") {
			typeName = "PassengerCar";
		}
		else if (vehicle.get()->getType() == "1")
		{
			typeName = "SleepingCar";
		}
		else if (vehicle.get()->getType() == "2") {
			typeName = "OpenFreightCar";
		}
		else if (vehicle.get()->getType() == "3")
		{
			typeName = "ClosedFreightCar";
		}
		else if (vehicle.get()->getType() == "4")
		{
			typeName = "electricalLocomotive";
		}
		else {
			typeName = "dieselLocomotive";
		}
		cout << "VehicleId: " << vehicle.get()->getId() << ", type: " << typeName << endl;
	}
}

