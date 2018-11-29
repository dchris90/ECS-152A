#include "Packet.h"


Packet::Packet()
{
}

Packet::Packet(double departure_time, double service_time)
{
	this->departure_time = departure_time;
	this->service_time = service_time;
}

Packet::~Packet()
{
}
