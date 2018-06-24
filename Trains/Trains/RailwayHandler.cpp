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

// Function that returns true if the different files could be read.
bool RailwayHandler::fileHandler(string stationfile, string trainfile, string trainmapfile)
{
	if (readStationsFromFile(stationfile)) {
		if (readTrainsFromFile(trainfile)) {
			return readTrainMapFromFile(trainmapfile);
		}
	}
	return false;
}

// Function that read Station file and creates needed vehicle objects.
bool RailwayHandler::readStationsFromFile(string filename)
{
	ifstream stationFile(filename);

	if (!stationFile.is_open()) {
		throw runtime_error("Error! Could not open file!");
	}
	else {

		//variables used for reading 
		int vehicleId;
		int vehicleType = 0;
		int id;
		string stationName;
		int loadCapacity = 0;
		int loadSurface = 0;
		int loadingVolume = 0;
		int nrOfSeats, beds, maxSpeed,  power;
		double fuelConsumption;
		bool internet;

		vector<string> lines;
		string line;

		while (getline(stationFile, line))
		{
			lines.push_back(line);
			istringstream iss(line);

			char delim;
			char delim2;

			iss >> stationName >> delim;			

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
			// add new station and new vehicles to stations vector
			stations.emplace_back(shared_ptr<Station>(new Station(stationName, vehicles)));
		}
		return true;
	}
}

// Function that read Train file and creates needed train objects.
bool RailwayHandler::readTrainsFromFile(string filename)
{
	ifstream trainFile(filename);

	if (!trainFile.is_open()) {
		throw runtime_error("Error! Could not open file!");
	}
	else {

		// variables used for reading file
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
			// save new train objects in vector of trains
			trains.emplace_back(shared_ptr<Train>(new Train(id, vehicleTypes, depStation, arrStation, schedDepTime, schedArrTime, maxSpeed)));
				}
		return true;
	}
}

// Function that read Trainmap file and creates needed distance objects.
bool RailwayHandler::readTrainMapFromFile(string filename)
{
	ifstream trainFile(filename);

	if (!trainFile.is_open()) {
		throw runtime_error("Error! Could not open file!");
	}
	else {
		// variables used for reading
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

// Function that starts the different events. 
void RailwayHandler::startEvents()
{
	// convert the trains schedule departure time from string into int
	for (auto train : trains) {
		int hh, mm;
		char delim;
		istringstream iss;
		iss.str(train->getSchedDepTime());
		iss >> hh >> delim >> mm;
		unsigned eventStartTime;
		eventStartTime = (hh*60+mm) - TIME_BUILD; // subtract 30 minutes from the trains scheduled dep time
		
		// create a build event, use train id as identifier
		sim->scheduleEvent(shared_ptr<Event>(new BuildEvent(sim, this, eventStartTime, train->getId())));
	}
}

// Function that try to build a train, if successful train state is set to assembled otherwise to incomplete
bool RailwayHandler::build(int trainId)
{
	vector<string> types;						// vector used for saving a trains different types
	bool found = false;

	for (auto train : trains) {
		if (trainId == train->getId()) {				// check for train id in train vector
			for (auto station : stations) {
				if (train->getDepStation() == station->getName()) {  // find a station that matches trains dep station
					types = train->getType();						// save trains needed types in vector
					for (auto type : types) { 
						if (station->findVehicle(vehiclePointer, type)) {		// find vehicle at station
							train->addVehiclesToTrain(vehiclePointer);			// add vehicle to train
							station->removeVehicleAtStation(vehiclePointer);	// remove added vehicle from station
							found = true;
						}
					}
					if (found)						// If the train has all its vehicles...
					{
						train->setState(ASSEMBLED);				// train state is set to assembled and saved in vector
						cout << "Time " << sim->getTime() << ": Train number: " << trainId << " has been assembled at station  " << train->getDepStation() << endl;;
						assembledTrains.emplace_back(train); 
						return true;
					}
					else
					{
						train->setState(INCOMPLETE);			// train state is set to incomplete and saved in vector
						cout << "Time " << sim->getTime() << ": Train number: " << trainId << " couldn't be assembled at station  " << train->getDepStation() << endl;
						incompleteTrains.emplace_back(train); 
						return false;
					}
				}
			}
		}
	}
}

// Function that set the train state to ready
void RailwayHandler::assembled(int trainId)
{
	for (auto train : assembledTrains) {				
		if (trainId == train->getId()) {
			train->setState(READY);
			cout << endl << "Time " << sim->getTime() << ": Train number: " << trainId << " is ready for departure at station " << train->getDepStation() << endl;
		}
	}
}

// Function that set the train state to Running
int RailwayHandler::isRunning(int trainId)
{
	// Convert arrival time string to int and return the arrivaltime to event function
	for (auto train : assembledTrains) {						
		if (trainId == train->getId()) {
			int arrivalTime = 0;
				int hh, mm;
				char delim;
				istringstream iss;
				iss.str(train->getSchedArrTime());
				iss >> hh >> delim >> mm;
				arrivalTime = (hh * 60 + mm);

			train->setState(RUNNING);
			cout << endl << "Time " << sim->getTime() << ": Train number: " << trainId << " just departed from station " << train->getDepStation() << endl;
			return arrivalTime;
		}
	}
}

// Function that set train state to arrived
void RailwayHandler::arrived(int trainId)
{
	for (auto train : assembledTrains) {					
		if (trainId == train->getId()) {
			train->setState(ARRIVED);
			cout << endl << "Time " << sim->getTime() << ": Train number " << trainId << " just arrived at station " << train->getArrStation() << endl;
		}
	}
}

// Function that set state to finished and returns vehicle to vehicles vector at end station
void RailwayHandler::end(int trainId)
{
	vector<string> types;
	for (auto train : assembledTrains) {						
		if (trainId == train->getId()) {
			for (auto station : stations) {
				if (train->getArrStation() == station->getName()) {
					types = train->getType();
					for (auto type : types) {
						if (station->findVehicle(vehiclePointer, type)) {		// find vehicles
							train->unloadVehiclesFromTrain(vehiclePointer);		// remove vehicles from train
							station->addVehicleToStation(vehiclePointer);	//return used vehicles to station
						}
					}
							train->setState(FINISHED);
							cout << endl << "Time " << sim->getTime() << ": Train number " << trainId << " has returned its vehicle at station " << train->getArrStation() << endl;					
				}
			}
		}
	}
}

// Function that finds a trains distance between depstation and arrstation. TODO handle delayed trains.
double RailwayHandler::calculateAverageSpeed(int trainId)
{
	double sum = 0;
	for (auto train : trains) {					
		if (trainId == train->getId()) {
			for (auto distance : stationDistance) {			
				if (train->getDepStation() == distance->getFrom() && train->getArrStation() == distance->getTo()) {
					int d = distance->getDistance();
					sum = train->calculateAverageSpeed(d); // pass distance to function in train class
					return sum;
				}
			}
		}
	}
}

void RailwayHandler::logToFile()
{
	ofstream logFile("Trainsim.log", ios_base::out | ios_base::app);
	//logFile << sim->getTime() << ":" << "Train with id: " << this-> << ":" << << ":" << "\n";
	logFile.close();
}

void RailwayHandler::printTrain(int trainId)
{
	vector<string> types;
	for (auto train : trains) {
		if (trainId == train->getId()) {
			double sum = this->calculateAverageSpeed(trainId);
			train->print(sum);
			/*
			types = train->getType();
			for (auto type : types) {
				//FUNKAR INTE SKA skriva ut vilka vehicles ocg id o typ för varje.
				type = vehiclePointer->getId();
				cout << type << endl;
			}*/
		}
	}
}

void RailwayHandler::printStation(string name)
{
	for (auto station : stations) {
		if (name == station->getName()) {
			station->print();
			for (auto train : assembledTrains) {
				if (train->getDepStation() == station->getName() || train->getArrStation() == station->getName()) {

					int state = train->getState();
					string convertedState = "";

					if (state == 0) {
						convertedState = "NOT_ASSEMBLED";
					}
					else if(state == 1) {
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

					cout << "Train: " << train->getId() << " in state: " << convertedState << " at station: " << station->getName() << endl;
				}
			}
		}
	}	
}
