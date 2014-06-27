#include <iostream>
#include <fstream>

#include "simulator.hpp"
#include "fcfs_scheduler.hpp"

// entry point
int main()
{
	try {
		std::ifstream resourcesStream("resources.txt");
		std::ifstream jobsStream("jobs.txt");

		FirstComeFirstServeScheduler fcfsScheduler;

		Simulator simulator(resourcesStream, jobsStream, fcfsScheduler);

		simulator.simulate();
		simulator.dumpOutputSequence(std::cout);

		return 0;
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception: " << e.what() << "\n";
		return 1;
	}

}
