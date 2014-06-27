/*
 * scheduler.h
 *
 *  Created on: Jun 27, 2014
 *      Author: aaghajanyan
 */

#ifndef SCHEDULER_H_
#define SCHEDULER_H_

#include "job.hpp"
#include "resource.hpp"
#include "job_assignment.hpp"

/**
 * Scheduler is an interface which abstracts away the implementation details of a particular scheduling algorithm.
 * To implement a new scheduling algorithm, simply implement this interface and hook it into the Simulator instance via
 * a constructor.
 * TODO: in real world we would likely do this via a factory pattern rather than direct constructor parameter passing.
 */
class Scheduler
{
public:
	/**
	 * virtual destructor.
	 */
	virtual ~Scheduler() = 0;

	/**
	 * Notify the scheduler that a Job was requested. Implementations typically will update their internal containers
	 * when this call is made.
	 *
	 * @param job the Job instance requested.
	 */
	virtual void jobRequested(const Job& job) = 0;

	/**
	 * Takes the set of available resources and makes a decision which Job to execute on which node, based on the
	 * current internal state of the Scheduler.
	 *
	 * @param resources the set of currently available resources.
	 * @return a JobAssignment instance instructing the caller to execute a specific job on a specific node. If no Job
	 * 	can be run at this moment, a no-op JobAssignment is returned (JobAssignment::isNoOp() == true).
	 */
	virtual JobAssignment assignJob(const Resources& resources) = 0;
};

#endif /* SCHEDULER_H_ */
