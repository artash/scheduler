/*
 * FirstComeFirstServeScheduler.cpp
 *
 *  Created on: Jun 27, 2014
 *      Author: aaghajanyan
 */
#include <set>


#include "resource.hpp"
#include "fcfs_scheduler.hpp"

FirstComeFirstServeScheduler::FirstComeFirstServeScheduler() {
}

FirstComeFirstServeScheduler::~FirstComeFirstServeScheduler() {
}

void FirstComeFirstServeScheduler::jobRequested(const Job& job)
{
	jobs.push_back(job);
}

JobAssignment FirstComeFirstServeScheduler::assignJob(const Resources& resources)
{
	// iterate through the list of jobs until we find one that can be executed with the resources available
	std::list<Job>::iterator it = jobs.begin();
	int nodeId;
	for(; it != jobs.end(); ++it)
	{
		if ( (nodeId = canRunJob(*it, resources)) > 0 )
		{
			return JobAssignment(nodeId, it->getId(), it->getUnits());
		}
	}
	// no job assigned, return an empty assignment
	return JobAssignment();

}

int FirstComeFirstServeScheduler::canRunJob(const Job& job, const Resources& resources)
{
	// we try to find the smallest resource available that can do the Job, i.e. the smallest unit value greater or equal
	// to the amount of units our job needs.
	Resource lbResource(0, job.getUnits());	// Create a fake Resource instance to be used with lower_bound
	return resources.lower_bound(lbResource) == resources.end() ? -1 : resources.lower_bound(lbResource)->getNode();
}

