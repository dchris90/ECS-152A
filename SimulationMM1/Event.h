#pragma once

class Event
{
public:
	Event();
	Event(double event_time, int event_type);
	~Event();

	static const int ARRIVAL_EVENT = 0;
	static const int DEPARTURE_EVENT = 1;

	double event_time;
	int event_type;
	Event *prev;
	Event *next;
};
