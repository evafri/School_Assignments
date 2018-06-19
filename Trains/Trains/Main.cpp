/*
File: Main.cpp
Purpose: This is where the program starts
Author: Eva Frisell <evmo1600>
Date: 2018-05-14
Version: 1.1
*/

#include <iostream>
#include <fstream>
#include <string>
#include "Station.h"
#include "StationHandler.h"

using namespace std;

int main() {

	StationHandler *stationhandler = new StationHandler();
	stationhandler->readFromFileHandler("TrainStations.txt", "Trains.txt", "TrainMap.txt");

	delete stationhandler;

	return 0;
}