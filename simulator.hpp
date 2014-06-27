/*
 * Simulator.h
 *
 *  Created on: Jun 27, 2014
 *      Author: aaghajanyan
 */

#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include <istream>
#include <sstream>
#include <vector>
#include <utility>
#include <string>
#include <set>
#include <map>

#include "scheduler.hpp"
#include "resource.hpp"
#include "simulator.hpp"

/**
 * The main simulation driver.
 */
class Simulator {
public:
	/**
	 * @param rs the stream of resource available events.
	 * @param js the stream of job requests.
	 * @param sched a concrete Scheduler implementation.
	 */
	Simulator(std::istream& rs, std::istream& js, Scheduler& sched);

	/**
	 * Main simulation loop.
	 */
	void simulate();

	/**
	 * After the simulation is completed, call this method to output the resulting sequence of actions.
	 */
	void dumpOutputSequence(std::ostream&) const;

private:
	// convenience method to do the string parsing. Is made a template to avoid code duplication for resource parsing
	// and job parsing.
	template<typename T>
	static std::vector<T> splitLineIntoPairs(const std::string& line);

	// process a newline separated line of resource available events from the input stream.
	void processResourcesChunk();

	// process a newline separated line of job requests from the input stream.
	void processJobsChunk();

	void scheduleJobs();

	std::istream& resourcesStream;
	std::istream& jobsStream;
	Scheduler& scheduler;

	// master resource table. This is a simple node id -> Resource mapping.
	std::map<int, Resource> resourcesMap;

	// a redundant container sorted by units
	Resources resources;

	// sequence of output actions
	std::vector<JobAssignment> outputSequence;

};

template<typename T>
std::vector<T> Simulator::splitLineIntoPairs(const std::string& line)
{
	std::vector<T> pairs;

	std::istringstream iss(line);
	char bracket;
	int left, right;

	while (iss)
	{
		if (!(iss >> bracket))
		{
			break;
		}
		if (bracket != '(')
		{
			throw std::runtime_error("Error parsing input line: " + line);
		}
		iss >> left >> right >> bracket;
		if (!iss || bracket != ')')
		{
			throw std::runtime_error("Error parsing input line: " + line);
		}
		pairs.push_back(T(left, right));
	}
	return pairs;
}


#endif /* SIMULATOR_H_ */
