/*
File: StationDistance.h
Purpose: Holds information about the distance between two stations
Author: Eva Frisell <evmo1600>
Date: 2018-06-11
Version: 1.1
*/

#ifndef STATIONDISTANCE_H
#define STATIONDISTANCE_H

#pragma once
#include <iostream>
#include <memory>
#include <vector>

using namespace std;

class StationDistance {
private:
	vector <shared_ptr<StationDistance>> stationDistance;
	string to;
	string from;
	int distance;

public:
	StationDistance(string to, string from, int distance) : to(to), from(from), distance(distance) {}
	~StationDistance(){}
};
#endif
