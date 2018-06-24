/*
File: Station.cpp
Purpose: Implementation of RailwayHandler.
Author: Eva Frisell <evmo1600>
Date: 2018-06-11
Version: 1.1
*/

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>
#include "RailwayHandler.h"
#include "StationDistance.h"

using namespace std;

struct myclass
{
	bool operator()(shared_ptr<Train> left, shared_ptr<Train> right)
	{
		return left.get()->getSchedDepTime() > right.get()->getSchedDepTime();
	}
} myobject;

bool RailwayHandler::fileHandler(string stationfile, string trainfile, string trainmapfile)
{
	if (readStationsFromFile(stationfile)) {
		if (readTrainsFromFile(trainfile)) {
			return readTrainMapFromFile(trainmapfile);
		}
	}
	return false;
}

bool RailwayHandler::readStationsFromFile(string filename)
{
	ifstream stationFile(filename);

	if (!stationFile.is_open()) {
		throw runtime_error("Error! Could not open file!");
	}
	else {

		//variables for reading
		int vehicleId;
		int vehicleType = 0;
		int id;
		string stationName;
		int nrOfSeats, beds, loadSurface, loadingVolume, maxSpeed, power;
		double loadCapacity, fuelConsumption;
		bool internet;

		vector<string> lines;
		string line;

		while (getline(stationFile, line))
		{
			lines.push_back(line);
			istringstream iss(line);

			char delim;
			char delim2;

			iss >> stationName >> delim;			  // read the station name and the '('

			while (iss >> vehicleId >> vehicleType) {

				id = vehicleId;
				
				switch (vehicleType) {

				case 0:
				{
					iss >> nrOfSeats >> internet >> delim >> delim2; //use delim and delim2 to read ( and )
					vehicles.emplace_back(shared_ptr<PassengerCar>(new PassengerCar(id, nrOfSeats, internet))); // skapa nytt objekt o spara i tåg? eller vehicek vecor?
					break;
				}
				case 1: {
					iss >> beds >> delim >> delim2; //use delim and delim2 to read ( and );
					vehicles.emplace_back(shared_ptr<SleepingCar>(new SleepingCar(id, beds)));
					break;
				}
				case 2: {
					iss >> loadCapacity >> loadSurface >> delim >> delim2; //use delim and delim2 to read ( and );
					vehicles.emplace_back(shared_ptr<OpenFreightCar>(new OpenFreightCar(id, loadCapacity, loadSurface)));
					break;
				}
				case 3: {
					iss >> loadingVolume >> delim >> delim2; //use delim and delim2 to read ( and );
					vehicles.emplace_back(shared_ptr<ClosedFreightCar>(new ClosedFreightCar(id, loadingVolume)));
					break;
				}
				case 4: {
					iss >> maxSpeed >> power >> delim >> delim2; //use delim and delim2 to read ( and );
					vehicles.emplace_back(shared_ptr<ElectricalLocomotive>(new ElectricalLocomotive(id, maxSpeed, power)));
					break;
				}
				case 5: {
					iss >> maxSpeed >> fuelConsumption >> delim >> delim2; //use delim and delim2 to read ( and );
					vehicles.emplace_back(shared_ptr<DieselLocomotive>(new DieselLocomotive(id, maxSpeed, fuelConsumption)));
					break;
				}
				}
			}
			stations.emplace_back(shared_ptr<Station>(new Station(stationName, vehicles)));
		}
		return true;
	}
}


bool RailwayHandler::readTrainsFromFile(string filename)
{
	ifstream trainFile(filename);

	if (!trainFile.is_open()) {
		throw runtime_error("Error! Could not open file!");
	}
	else {
		int trainId;
		int id;
		int vehicleType = 0;
		string schedDepTime, schedArrTime;
		string depStation, arrStation;
		double maxSpeed;

		vector<string> lines;
		string line;

		while (getline(trainFile, line))
		{
			lines.push_back(line);
			istringstream iss(line);

			iss >> trainId >> depStation >> arrStation >> schedDepTime >> schedArrTime >> maxSpeed;

			id = trainId;

			while (iss >> vehicleType) {
				string type = to_string(vehicleType);
				vehicleTypes.push_back(type);
				}
			trains.emplace_back(shared_ptr<Train>(new Train(id, vehicleTypes, depStation, arrStation, schedDepTime, schedArrTime, maxSpeed)));
				}
		return true;
	}
}

bool RailwayHandler::readTrainMapFromFile(string filename)
{
	ifstream trainFile(filename);

	if (!trainFile.is_open()) {
		throw runtime_error("Error! Could not open file!");
	}
	else {

		string to;
		string from;
		int distance;
		vector<string> lines;
		string line;

		while (getline(trainFile, line))
		{
			lines.push_back(line);
			istringstream iss(line);
			iss >> to >> from >> distance;

			stationDistance.emplace_back(shared_ptr<StationDistance>(new StationDistance(to, from, distance)));
		}
		return true;
	}
}

void RailwayHandler::startEvents()
{
	// starta upp allt 
	char delim;

	//sort(trains.begin(), trains.end(), myobject);

	for (auto train : trains) {
		int hh, mm;
		istringstream iss;
		iss.str(train->getSchedDepTime());
		iss >> hh >> delim >> mm;
		unsigned eventStartTime;
		eventStartTime = (hh*60+mm) - TIME_BUILD;
		
		sim->scheduleEvent(new BuildEvent(sim, this, eventStartTime, train->getId()));
	}
}

bool RailwayHandler::build(int trainId)
{
	vector<string> types;
	bool found = false;

	for (auto train : trains) {
		if (trainId == train->getId()) {
			for (auto station : stations) {
				if (train->getDepStation() == station->getName()) {
					types = train->getType();
					for (auto type : types) {
						if (station->findVehicle(vehiclePointer, type)) {
							train->addVehiclesToTrain(vehiclePointer);			// måste veta id på vehicle som sökts fram lägga till
							station->removeVehicleAtStation(vehiclePointer);			// ta bort från stationen
							found = true;
						}
					}
					if (found)
					{
						train->setState(ASSEMBLED);
						cout << "Time " << sim->getTime() << ": Train number: " << trainId << " has been assembled at station  " << train->getDepStation() << endl;;
						assembledTrains.emplace_back(train); 
						return true;
					}
					else
					{
						train->setState(INCOMPLETE); 
						cout << "Time " << sim->getTime() << ": Train number: " << trainId << " couldn't be assembled at station  " << train->getDepStation() << endl;
						incompleteTrains.emplace_back(train); 
						return false;
					}
				}
			}
		}
	}
}

bool RailwayHandler::assembled(int trainId)
{
	for (auto train : assembledTrains) {				
		if (trainId == train->getId()) {
			train->setState(READY);

			cout << endl << "Time " << sim->getTime() << ": Train number: " << trainId << " is ready for departure at station " << train->getDepStation() << endl;
			
			return true;
		}
	}
}

bool RailwayHandler::isRunning(int trainId)
{
	for (auto train : assembledTrains) {						
		if (trainId == train->getId()) {
			train->setState(RUNNING);

			cout << endl << "Time " << sim->getTime() << ": Train number: " << trainId << " just departed from station " << train->getDepStation() << endl;
			
			return true;
		}
	}

	
	// senhantering
	return false;
}

bool RailwayHandler::arrived(int trainId)
{
	for (auto train : assembledTrains) {					
		if (trainId == train->getId()) {
			train->setState(ARRIVED);

			cout << endl << "Time " << sim->getTime() << ": Train number " << trainId << " just arrived at station " << train->getArrStation() << endl;
			
			return true;
		}
	}

	
	
	// senhantering
	return false;
}

bool RailwayHandler::end(int trainId)
{
	vector<string> types;

	for (auto train : assembledTrains) {						
		if (trainId == train->getId()) {
			for (auto station : stations) {
				if (train->getArrStation() == station->getName()) {
					types = train->getType();
					for (auto type : types) {
						if (station->findVehicle(vehiclePointer, type)) {
							train->unloadVehiclesFromTrain(vehiclePointer);
							train->setState(FINISHED);

							cout << endl << "Time " << sim->getTime() << ": Train number " << trainId << "has returned its vehicle at station " << train->getArrStation() << endl;

							return true;
						}
					}
				}
			}
		}
	}
}

double RailwayHandler::calculateAverageSpeed(int trainId)
{
	double sum = 0;
	for (auto train : trains) {					
		if (trainId == train->getId()) {
			for (auto distance : stationDistance) {
				if (train->getDepStation() == distance->getFrom() && train->getArrStation() == distance->getTo()) {
					int d = distance->getDistance();
					sum = train->calculateAverageSpeed(d);
					return sum;
				}
			}
		}
	}
}

void RailwayHandler::logToFile()
{
}

void RailwayHandler::printTrain(int trainId)
{
	for (auto train : trains) {
		if (trainId == train->getId()) {
			double sum = this->calculateAverageSpeed(trainId);
			train->print(sum);
		}
	}
	// call print funktion in train + add average speed
}

void RailwayHandler::printStation(string name)
{
	for (auto station : stations) {
		if (name == station->getName()) {
			station->print();
			for (auto train : trains) {
				if (train->getDepStation() == station->getName() || train->getArrStation() == station->getName()) {
					cout << "Train: " << train->getId() << " in state: " << train->getState() << " at station: " << station->getName() << endl;
				}
			}
		}
	}	
}
