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
const int TIME_READY = 10;						// 10 min before take-off
const int TIME_DELAY = 10;						// If train is not built, delay in 10. TODO
const int TIME_FINISHED = 20;					// After 20 min in arrived..
const int SIM_TIME = 1439;						// Duration of simulation

