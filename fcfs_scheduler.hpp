/*
 * FirstComeFirstServeScheduler.h
 *
 *  Created on: Jun 27, 2014
 *      Author: aaghajanyan
 */

#ifndef FIRSTCOMEFIRSTSERVESCHEDULER_H_
#define FIRSTCOMEFIRSTSERVESCHEDULER_H_

#include <list>

#include "scheduler.hpp"
#include "job.hpp"

/**
 * A simple scheduling algorithm which assigns jobs on a first come, first serve basis. Every job request is queued
 * and is executed as soon as a big enough (in terms of units) resource is available.
 *
 */
class FirstComeFirstServeScheduler: public Scheduler {
public:
	FirstComeFirstServeScheduler();

	virtual ~FirstComeFirstServeScheduler();
	virtual void jobRequested(const Job& job);
	virtual JobAssignment assignJob(const Resources& resources);

private:
	// since we are first come first serve, we'll be only adding to the tail and iterating sequentially. list should
	// be good for this purpose.
	std::list<Job> jobs;

	/**
	 * Check if a given job can be run with the set of resources available.
	 *
	 * @param job the job to check.
	 * @param resources the set of currently available resources to use.
	 * @return the node id of the node that shall run the job if it is possible to run this job, -1 otherwise.
	 */
	int canRunJob(const Job& job, const Resources& resources);
};

#endif /* FIRSTCOMEFIRSTSERVESCHEDULER_H_ */
