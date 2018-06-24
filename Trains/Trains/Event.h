/*
File: Event.h
Purpose: Definition of abstract class Event and derived concrete Event classes.
Author: Örjan Sterner
Modified by: Eva Frisell <evmo1600>
Date: 2018-06-11
Version: 1.1
*/

#ifndef EVENT_H
#define EVENT_H
#include <memory>
using namespace std;

// Forward declarations
class Simulation;
class RailwayHandler;

class Event {
public:
	// Constructor requires time of event
	Event(unsigned int t) : time(t) { }

	virtual ~Event() { }

	// Process event by invoking this method
	virtual void processEvent(bool keepOn) = 0;

	// Get time for this event
	unsigned int getTime() const {
		return time;
	}

protected:
	// Time for this event
	unsigned int time;
};

// Used to compare to Events with respect to time
class EventComparison {
public:
	bool operator() (shared_ptr<Event> left, shared_ptr<Event> right) {
		return left.get()->getTime() > right.get()->getTime();
	}
};

class BuildEvent : public Event {
public:
	BuildEvent(Simulation *sim, RailwayHandler *railwayHandler, int time, int trainId)
		: Event(time), sim(sim), railwayHandler(railwayHandler), trainId(trainId) { }

	virtual void processEvent(bool keepOn);

protected:
	int trainId;
	Simulation *sim;
	RailwayHandler *railwayHandler;
};

class ReadyEvent : public Event {
public:
	ReadyEvent(Simulation *sim, RailwayHandler *railwayHandler, int time, int trainId)
		: Event(time), sim(sim), railwayHandler(railwayHandler), trainId(trainId) { }

	virtual void processEvent(bool keepOn);

protected:
	int trainId;
	Simulation *sim;
	RailwayHandler *railwayHandler;
};



class LeaveEvent : public Event {
public:
	LeaveEvent(Simulation *sim, RailwayHandler *railwayHandler, int time, int trainId)
		:Event(time), sim(sim), railwayHandler(railwayHandler), trainId(trainId) { }

	virtual void processEvent(bool keepOn);

protected:
	int trainId;
	Simulation *sim;
	RailwayHandler *railwayHandler;
};



class ArriveEvent : public Event {
public:
	ArriveEvent(Simulation *sim, RailwayHandler *railwayHandler, int time, int trainId)
		:Event(time), sim(sim), railwayHandler(railwayHandler), trainId(trainId) { }

	virtual void processEvent(bool keepOn);

protected:
	int trainId;
	Simulation *sim;
	RailwayHandler *railwayHandler;
};


class FinishEvent : public Event {
public:
	FinishEvent(Simulation *sim, RailwayHandler *railwayHandler, int time, int trainId)
		:Event(time), sim(sim), railwayHandler(railwayHandler), trainId(trainId) { }

	virtual void processEvent(bool keepOn);

protected:
	int trainId;
	Simulation *sim;
	RailwayHandler *railwayHandler;
};

#endif