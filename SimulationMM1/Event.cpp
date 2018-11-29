#include "Event.h"


Event::Event()
{
}

Event::Event(double event_time, int event_type)
{
	this->event_time = event_time;
	this->event_type = event_type;
	prev = nullptr;
	next = nullptr;
}

Event::~Event()
{
}
