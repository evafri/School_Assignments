/*
File: Constants.h
Purpose: Holds needed constants
Author: Eva Frisell <evmo1600>
Date: 2018-06-11
Version: 1.1
*/

// A trains differents states during its life
enum State {NOT_ASSEMBLED, INCOMPLETE, ASSEMBLED, READY, RUNNING, ARRIVED, FINISHED};

// Time variables used in simulation

const int TIME_INTERVAL_DEFAULT = 1;
const int TIME_INTERVAL = 10;					// time interval for user
const int TIME_BUILD = 30;						// train build is 30 min before dep time
const int TIME_READY = 20;						// 10 min before take-off or from 20 to 10 min interval?
const int TIME_DEPARTURE = 10;					// Time train departs 10 min before?
const int TIME_DELAY = 10;						// If train is not built, delay in 10
const int TIME_FINISHED = 20;					// After 20 min in arrived..

const int SIM_TIME = 1439; // Duration of simulation

//const string SIM_START = "00:00";
//const string SIM_END = "23:59";
