/*
File: Station.cpp
Purpose: Implementation of Stations
Author: Eva Frisell <evmo1600>
Date: 2018-06-11
Version: 1.1
*/

# include <fstream>
# include <sstream>
#include <iostream>
#include <string>
#include "StationHandler.h"
#include "StationDistance.h"

using namespace std;

bool StationHandler::readFromFileHandler(string stationfile, string trainfile, string trainmapfile)
{
	if (readStationsFromFile(stationfile)) {
		if (readTrainsFromFile(trainfile)) {
			return readTrainMapFromFile(trainmapfile);
		}
	}
	return false;
}

bool StationHandler::readStationsFromFile(string filename)
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

		//stations.clear();
		//vehicles.clear();

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


bool StationHandler::readTrainsFromFile(string filename)
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
			vector<string>vehicleTypes;
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

bool StationHandler::readTrainMapFromFile(string filename)
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
