#pragma once

class Packet
{
public:
	Packet();
	Packet(double departure_time, double service_time);	
	~Packet();

	double departure_time;
	double service_time;
};
