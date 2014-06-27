/*
 * Job.h
 *
 *  Created on: Jun 27, 2014
 *      Author: aaghajanyan
 */

#ifndef JOB_H_
#define JOB_H_
/**
 * Job represents a piece of work that cannot be split across nodes. It consists of the processing units required and
 * time steps. It also has an id which is auto-assigned - the real id is not relevant for simulation purposes.
 */
class Job {
public:
	Job()
		: id(getNextId())
		, units(0)
		, timeSteps(0)
	{
	}

	Job(int units, int timeSteps)
		: id(getNextId())
		, units(units)
		, timeSteps(timeSteps)
	{
	}

	int getUnits() const
	{
		return units;
	}

	int getTimeSteps() const
	{
		return timeSteps;
	}

	int getId() const
	{
		return id;
	}

private:
	// this method is not thread safe. It's ok for us since we're simulating events which never race with
	// each other.
	int getNextId() const
	{
		static int NEXT_ID = 0;
		return ++NEXT_ID;
	}

	int id;
	int units;
	int timeSteps;


};

#endif /* JOB_H_ */
