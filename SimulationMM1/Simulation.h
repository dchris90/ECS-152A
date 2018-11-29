#pragma once

#include "GEL.h"
#include "Packet.h"
#include <queue>
using namespace std;

typedef struct
{
	double mean_fifo_len;
	double utilization;
	int dropped_packets;
} Result;

class Simulation
{
public:
	Simulation();
	~Simulation();

	void Initialize(double lambda, double mu, int packets_num, int max_fifo_len);
	Result Run();

private:
	double lambda;						// Packets arrival speed
	double mu;							// Packets processing speed
	int packets_num;					// Number of packets to simulate
	int max_fifo_len;					// Max packets FIFO can hold

	double sim_time;							// Current simulation time
	double last_packet_departure_time;
	double last_event_time;
	int length;								// Current FIFO buffer length
	queue<Packet> fifo_buffer;				// FIFO buffer
	double arrivalTime;						// Holds inter packet time span
	double serviceTime;						// Holds time to process packet
	GEL *gel;								// Global event list
	Event *arrivalEvent;
	Event *departureEvent;	

	int dropped_packets;
	double fifo_area;
	double total_service_time;
	Result result;

	double GetPacketArrivalTimeOrServiceTime(double rate);
	void CreateArrivalEvent();
};
