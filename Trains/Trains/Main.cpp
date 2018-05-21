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
using namespace std;

int main() {
	string line;
	//ifstream myfile("Trains.txt");
	//ifstream myfile("TrainStations.txt");
	ifstream myfile("TrainMap.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			cout << line << '\n';
		}
		myfile.close();
	}

	else cout << "Unable to open file";

	return 0;
}