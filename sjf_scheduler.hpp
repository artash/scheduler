/*
 * ShortestJobFirstScheduler.h
 *
 *  Created on: Jun 27, 2014
 *      Author: aaghajanyan
 */

#ifndef SHORTESTJOBFIRSTSCHEDULER_H_
#define SHORTESTJOBFIRSTSCHEDULER_H_

#include "resource.hpp"
#include "scheduler.hpp"

/**
 * An alternative implementation of a scheduler which gives a priority to short-lived Job requests when multiple jobs
 * are queued for execution. Consider a situation when you have a long-lasting job request (e.g. units:10, time:100)
 * and then immediately after that 20 short-lived job requests (e.g. units:10, time:1). With first come first served
 * approach, each of the 20 short-lived jobs will wait >100 time units. This scheduler is designed to solve that problem.
 */
class ShortestJobFirstScheduler: public Scheduler {
public:
	ShortestJobFirstScheduler();
	virtual ~ShortestJobFirstScheduler();

	virtual void jobRequested(const Job& job);
	virtual JobAssignment assignJob(const Resources& resources);
};

#endif /* SHORTESTJOBFIRSTSCHEDULER_H_ */
