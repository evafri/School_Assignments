/*
File: Station.cpp
Purpose: Implementation of Stations
Author: Eva Frisell <evmo1600>
Date: 2018-06-11
Version: 1.1
*/

#include "Station.h"
#include <algorithm>

using namespace std;
/*
struct isValue
{
	//int m_id;
	string m_type;

	//isValue(int id) : m_id(id) {}
	isValue(string type) : m_type(type) {}

	bool operator()(shared_ptr<Vehicle> v) const
	{
		return (v->getType() == m_type);
	}
};*/

// Function that adds a vehicle to the station. Used when a train has arrived, and the different carriages needs to be 
// returned to the vector of vehicles
void Station::addVehicleToStation(shared_ptr<Vehicle> vehicle)
{
		vehicles.emplace_back(vehicle);	
}

// Function used for finding a vehicle in the vehicles vector. 
bool Station::findVehicle(shared_ptr<Vehicle> &vehicle, string type)
{
	string typeName;

	if (type == "0") {
		typeName = "PassengerCar";
	}
	else if (type == "1")
	{
		typeName = "SleepingCar";
	}
	else if (type == "2") {
		typeName = "OpenFreightCar";
	}
	else if (type == "3")
	{
		typeName = "ClosedFreightCar";
	}
	else if (type == "4")
	{
		typeName = "electricalLocomotive";
	}
	else {
		typeName = "dieselLocomotive";
	}

	auto it = find_if(vehicles.begin(), vehicles.end(), [&typeName](const shared_ptr<Vehicle> &v) {return v->getType() == typeName; });
	if (it != vehicles.end())
	{
		vehicle = *it;  // return the found vehicle
		return true;
	}
	return false;
}

// Function uses for removing a vehicle from the vector of vehicles
bool Station::removeVehicleAtStation(shared_ptr<Vehicle> vehicle)
{
	auto item = std::find(vehicles.begin(), vehicles.end(), vehicle);

	if (item == vehicles.end()) {
		return false;
	}
	else {
		vehicles.erase(item);
		return true;
	}
}

// Function for printing
void Station::print()
{
	cout << endl << "Station name: " << name << endl;
	cout << "Total number of vehicles at the station: " << vehicles.size() << endl << endl;

	for (auto vehicle : vehicles) {
			vehicle->print();
		cout << endl;
	}
}
