/*
 * Simulator.cpp
 *
 *  Created on: Jun 27, 2014
 *      Author: aaghajanyan
 */

#include <istream>
#include <iostream>
#include <stdexcept>
#include <sstream>

#include "scheduler.hpp"
#include "resource.hpp"
#include "job.hpp"
#include "job_assignment.hpp"
#include "simulator.hpp"

Simulator::Simulator(std::istream& rs, std::istream& js, Scheduler& sched)
	: resourcesStream(rs)
	, jobsStream(js)
	, scheduler(sched)
{

}

void Simulator::simulate()
{
	if (!resourcesStream)
	{
		throw std::runtime_error("bad resource stream");
	}
	if (!jobsStream)
	{
		throw std::runtime_error("bad jobs stream");
	}

	std::string resourceLine;
	std::string jobsLine;

	// read one line at a time from resources stream and jobs stream. A line of data in each stream represents events
	// arrived in a given discrete time moment. If the resource stream has data on line N and jobs stream also has data
	// on that same line N, we'll assume that resource available events happen before job requests, even though they
	// happened at the same discrete time moment. An empty line in each of these streams represents a time tick with no
	// data.
	while (resourcesStream && jobsStream)
	{
		processResourcesChunk();
		processJobsChunk();
		scheduleJobs();
	}

	// drain resources stream if it has more items
	while (resourcesStream)
	{
		processResourcesChunk();
		scheduleJobs();
	}

	// drain jobs stream if it has more items
	while (jobsStream)
	{
		processJobsChunk();
		scheduleJobs();
	}
}

void Simulator::processResourcesChunk()
{
	std::string resourceLine;
	std::getline(resourcesStream, resourceLine);
	std::vector<Resource> resChunk;
	if (!resourceLine.empty())
	{
		resChunk = Simulator::splitLineIntoPairs<Resource>(resourceLine);
	}
	std::cout << "read " << resChunk.size() << " resources from resource file: " << resourceLine;

	// add new resources to the master resource table
	std::vector<Resource>::iterator it = resChunk.begin();
	for(; it != resChunk.end(); ++it)
	{
		resourcesMap[it->getNode()] += *it;
	}

	// redundantly copy the Resource instances into a set for easy lookup during job-node matching process
	resources.clear();
	std::map<int, Resource>::iterator it1 = resourcesMap.begin();
	for(; it1 != resourcesMap.end(); ++it1)
	{
		resources.insert(it1->second);
	}
}

void Simulator::processJobsChunk()
{
	std::string jobsLine;
	std::getline(jobsStream, jobsLine);
	std::vector<Job> jobs;
	if (!jobsLine.empty())
	{
		jobs = Simulator::splitLineIntoPairs<Job>(jobsLine);
	}
	std::cout << "read " << jobs.size() << " jobs from jobs file: " << jobsLine;

	std::vector<Job>::iterator it = jobs.begin();
	for(; it != jobs.end(); ++it)
	{
		scheduler.jobRequested(*it);
	}
}

void Simulator::scheduleJobs()
{
	JobAssignment jobAssignment;
	for(;;)
	{
		jobAssignment = scheduler.assignJob(resources);
		if (jobAssignment.isNoOp())
		{
			break;
		}

		// adjust the resources available
		int nodeId = jobAssignment.getNodeId();
		Resource resource = resourcesMap[nodeId];		// TODO error handling - what if not found?
		Resource adjustedResource(resource.getNode(), resource.getUnits() - jobAssignment.getUnits());
		resourcesMap[nodeId] = adjustedResource;
		outputSequence.push_back(jobAssignment);
	}
}

void Simulator::dumpOutputSequence(std::ostream& os) const
{
	for( int i = 0; i < outputSequence.size(); ++i)
	{
		// operator<< is overloaded for JobAssignment
		os << outputSequence[i] << "\n";
	}

}
