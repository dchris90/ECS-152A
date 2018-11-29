#include "Simulation.h"
#include <iostream>
using namespace std;


void Experiment(Simulation simulation)
{
	char input[20];

	int packets_num;
	vector<double> lambda1 = { 0.1, 0.25, 0.4, 0.55, 0.65, 0.80, 0.90 };
	vector<double> lambda2 = { 0.2, 0.4, 0.6, 0.8, 0.9 };
	double mu = 1.0;
	vector<int> max_fifo_len = { 1, 20, 50 };	

label_1:
	cout << "Input value for packets count to simulate: ";
	cin >> input;
	packets_num = atoi(input);

	if (packets_num == 0)
	{
		cout << "Value is not valid." << endl;
		goto label_1;
	}

	for (int i = 0; i < lambda1.size(); i++)
	{
		double lambda = lambda1[i];
		double ro = lambda / mu;
		simulation.Initialize(lambda, mu, packets_num, 0);
		Result result = simulation.Run();

		cout << "Lambda = " << lambda << ", mu = " << mu << ", max queue length = inf." << endl;
		cout << "Experiment mean queue length = " << result.mean_fifo_len << ", calculated queue length = " << ro / (1 - ro) << "." << endl;
		cout << "Experiment utilization = " << result.utilization << ", calculated utilization = " << ro * 100.0 << "." << endl;
	}

	for (int i = 0; i < lambda2.size(); i++)
	{
		for (int j = 0; j < max_fifo_len.size(); j++)
		{
			double lambda = lambda2[i];
			simulation.Initialize(lambda, mu, packets_num, max_fifo_len[j]);
			Result result = simulation.Run();

			cout << "Lambda = " << lambda << ", mu = " << mu << ", max queue length = " << max_fifo_len[j] << "." << endl;
			cout << "Number of dropped packets = " << result.dropped_packets << "." << endl;
		}
	}
}

void FreeSimulation(Simulation simulation)
{
	char input[20];

	double lambda;						// Packet arrival speed
	double mu;							// Packet processing speed
	int packets_num;					// Number of packets to simulate
	int max_fifo_len;					// Max packets FIFO buffer can hold

	/*	Set simulation parameters	*/
label_1:
	cout << "Input value for lambda (packets/seconds): ";
	cin >> input;
	lambda = atof(input);

	if (lambda == 0.0)
	{
		cout << "Value is not valid." << endl;
		goto label_1;
	}	

label_2:
	cout << "Input value for mu (packets/seconds): ";
	cin >> input;
	mu = atof(input);

	if (mu == 0.0)
	{
		cout << "Value is not valid." << endl;
		goto label_2;
	}

label_3:
	cout << "Input value for packets count to simulate: ";
	cin >> input;
	packets_num = atoi(input);

	if (packets_num == 0)
	{
		cout << "Value is not valid." << endl;
		goto label_3;
	}

label_4:
	cout <<"Input value for FIFO buffer length (set 0 for infininite length): ";
	cin >> input;
	max_fifo_len = atoi(input);

	if (max_fifo_len < 0)
	{
		cout << "Error: FIFO buffer length must be >= 0.";
		goto label_4;
	}

	/*	Initialization	*/
	simulation.Initialize(lambda, mu, packets_num, max_fifo_len);

	/* Run */
	Result result = simulation.Run();

	cout << "Utilization = " << result.utilization << "%." << endl;
	cout << "Mean queue length = " << result.mean_fifo_len << "." << endl;
	cout << "Number of dropped packets = " << result.dropped_packets << "." << endl;
}

int main()
{
	char input[20];

	string s;
	int simulation_type;
	Simulation simulation;

	do
	{
	label_1:
		cout << "Select simulation type:\n1 - Experiment\n2 - Free simulation\n>";

		try
		{
			cin >> input;
			simulation_type = atoi(input);

			switch (simulation_type)
			{
			case 1:
				Experiment(simulation);
				break;
			case 2:
				FreeSimulation(simulation);
				break;
			default:				
				cout << "Error: You must type either 1 or 2.";
				goto label_1;
			}
		}

		catch (exception ex)
		{			
			cout << "Error: " << ex.what();
			goto label_1;
		}
		
		cout << "Run new simulation [yes/no]: ";
		cin >> input;
		s = input;

	} while (s == "yes");

	return 0;
}
