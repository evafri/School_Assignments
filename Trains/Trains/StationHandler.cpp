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


using namespace std;

bool StationHandler::readFromFileHandler(string stationfile)
{
	if (readStationsFromFile(stationfile)) {
		return true;
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
		string type;
		int id;
		string stationName;
		int nrOfSeats, beds, loadSurface, loadingVolume, maxSpeed, power;
		double loadCapacity, fuelConsumption;
		bool internet;
		string para0, para1;

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


void StationHandler::readTrainsFromFile(string filename)
{
}

void StationHandler::readTrainMapFromFile(string filename)
{
}
