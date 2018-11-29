#include "Simulation.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>


Simulation::Simulation()
{
	// Initialize random seed
	srand((unsigned)time(NULL));
}

Simulation::~Simulation()
{
}

void Simulation::Initialize(double lambda, double mu, int packets_num, int max_fifo_len)
{
	this->lambda = lambda;
	this->mu = mu;
	this->packets_num = packets_num;
	this->max_fifo_len = max_fifo_len;

	sim_time = 0.0;
	last_packet_departure_time = 0.0;
	last_event_time = 0.0;
	length = 0;
	fifo_area = 0.0;
	dropped_packets = 0;
	total_service_time = 0.0;
	
	gel = new GEL();
}

void Simulation::CreateArrivalEvent()
{
	arrivalTime = GetPacketArrivalTimeOrServiceTime(lambda);
	sim_time += arrivalTime;
	arrivalEvent = new Event(sim_time, Event::ARRIVAL_EVENT);
	// Insert event in GEL
	gel->InsertEvent(arrivalEvent);
}

double Simulation::GetPacketArrivalTimeOrServiceTime(double rate)
{
	double u = (double)rand() / (RAND_MAX + 1);
	return (-1.0 / rate) * log(1 - u);
}

Result Simulation::Run()
{
	// Create arrival event
	CreateArrivalEvent();

	Event *curr_event = nullptr;

	int j = 1;

	while (!gel->IsEmpty())
	{
		// Get event from GEL
		curr_event = gel->GetHead();

		// Update statistics
		fifo_area += (curr_event->event_time - last_event_time) * length;
		last_event_time = curr_event->event_time;

		if (curr_event->event_type == Event::ARRIVAL_EVENT)
		{
			/*	Process arrival event	*/

			// Increment FIFO buffer size
			length++;

			// Check if buffer size is limited and full 
			if (max_fifo_len != 0 && length > max_fifo_len)
			{
				// Buffer is full
				// Set length back to max_fifo_length and increment dropped packets
				length--;
				dropped_packets++;
			}

			else
			{
				// Buffer still has space
				// Calculate packet service time
				serviceTime = GetPacketArrivalTimeOrServiceTime(mu);
				// Set current packet departure time
				last_packet_departure_time = fifo_buffer.size() == 0 ? sim_time + serviceTime : last_packet_departure_time + serviceTime;
				// Create packet
				Packet pkt(last_packet_departure_time, serviceTime);
				// Enque packet in FIFO
				fifo_buffer.push(pkt);
				// Create departure event					
				departureEvent = new Event(last_packet_departure_time, Event::DEPARTURE_EVENT);
				// Insert event in GEL
				gel->InsertEvent(departureEvent);
			}

			// Create arrival event
			if (++j <= packets_num)
			{
				if (j % 1000 == 0)
				{
					cout << ".";
				}

				CreateArrivalEvent();
			}
		}
		else
		{
			/*	Process departure event		*/

			// Dequeue FIFO buffer and decrement buffer length
			Packet pkt = fifo_buffer.front();
			fifo_buffer.pop();
			total_service_time += pkt.service_time;
			length--;
		}

		delete curr_event;
	}

	cout << endl;

	result.utilization = 100.0 * total_service_time / last_event_time;
	result.mean_fifo_len = fifo_area / last_event_time;
	result.dropped_packets = dropped_packets;

	return result;
}
